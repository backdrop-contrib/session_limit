<?php

/**
 * @file
 * Administrator forms for configuring simultaneous session limits.
 */

function session_limit_settings() {
  $form['session_limit_max'] = array(
    '#type' => 'textfield',
    '#title' => t('Default maximum number of active sessions'),
    '#default_value' => config_get('session_limit.settings', 'session_limit_max'),
    '#size' => 2,
    '#maxlength' => 3,
    '#description' => t('The maximum number of active sessions a user can have. 0 implies unlimited sessions.'),
  );

  $form['session_limit_include_root_user'] = array(
    '#type' => 'checkbox',
    '#title' => t('Apply limit to root admin user.'),
    '#description' => t('By default session limits do not apply to user #1'),
    '#default_value' => config_get('session_limit.settings', 'session_limit_include_root_user'),
  );

  $limit_behaviours = array(
    SESSION_LIMIT_DO_NOTHING => t('Do nothing.'),
    SESSION_LIMIT_DROP => t('Automatically drop the oldest sessions without prompting.'),
    SESSION_LIMIT_DISALLOW_NEW => t('Prompt to disconnect extra sessions.'),
  );

  $form['session_limit_behaviour'] = array(
    '#type' => 'radios',
    '#title' => t('When the session limit is exceeded'),
    '#default_value' => config_get('session_limit.settings', 'session_limit_behaviour'),
    '#options' => $limit_behaviours,
  );

  if (module_exists('masquerade')) {
    $form['session_limit_masquerade_ignore'] = array(
      '#type' => 'checkbox',
      '#title' => t('Ignore masqueraded sessions.'),
      '#description' => t("When a user administrator uses the masquerade module to impersonate a different user, it won't count against the session limit counter"),
      '#default_value' => config_get('session_limit.settings', 'session_limit_masquerade_ignore'),
    );
  }
  $form['session_limit_logged_out_message_severity'] = array(
    '#type' => 'select',
    '#title' => t('Logged out message severity'),
    '#default_value' => config_get('session_limit.settings', 'session_limit_logged_out_message_severity'),
    '#options' => array(
      'error' => t('Error'),
      'warning' => t('Warning'),
      'status' => t('Status'),
      '_none' => t('No Message'),
    ),
    '#description' => t('The Backdrop message type.  Defaults to Error.'),
  );

  $form['session_limit_logged_out_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Logged out message'),
    '#default_value' => config_get('session_limit.settings', 'session_limit_logged_out_message'),
    '#description' => t('The message that is displayed to a user if the workstation has been logged out.<br />
      @number is replaced with the maximum number of simultaneous sessions.'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#validate' => array('session_limit_settings_validate'),
    '#submit' => array('session_limit_settings_submit'),
  );
  return $form;
}

/**
 * Settings validation form.
 */
function session_limit_settings_validate($form, &$form_state) {
  $maxsessions = $form_state['values']['session_limit_max'];
  if (!is_numeric($maxsessions)) {
    form_set_error('session_limit_max', t('You must enter a number for the maximum number of active sessions.'));
  }
  elseif ($maxsessions < 0) {
    form_set_error('session_limit_max', t('Maximum number of active sessions must be positive.'));
  }
}

/**
 * Submit handler session limit configuration form.
 */
function session_limit_settings_submit($form, &$form_state) {
  foreach ($form_state['values'] as $key => $variable) {
    if (strpos($key, 'session_limit') === 0) {
      config('session_limit.settings')
        ->set($key, $variable)
        ->save();
    }
  }

  watchdog('session_limit', 'Session limits modified.', array(), WATCHDOG_INFO);
}

/**
 * Settings by role form.
 */
function session_limit_settings_byrole() {
  $config = config_get('session_limit.settings');

  $roles = user_roles(TRUE);
  foreach ($roles as $rid => $role) {
    $form["session_limit_rid_$rid"] = array(
      '#type' => 'select',
      '#options' => _session_limit_user_options(),
      '#title' => check_plain($role),
      '#default_value' => empty($config["session_limit_rid_$rid"]) ? 0 : (int)$config["session_limit_rid_$rid"],
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save permissions'),
  );

  return $form;
}

/**
 * Set session limits by role form submission.
 */
function session_limit_settings_byrole_submit($form, &$form_state) {
  foreach ($form_state['values'] as $setting_name => $setting_limit) {
    if (strpos($setting_name, 'session_limit') === 0) {
      config_set('session_limit.settings', $setting_name, $setting_limit);
    }
  }

  backdrop_set_message(t('Role settings updated.'), 'status');
  watchdog('session_limit', 'Role limits modified.', array(), WATCHDOG_INFO);
}
