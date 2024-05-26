
asm(".global pthread_atfork\n"
    ".type pthread_atfork @function\n"
    "pthread_atfork:\n");

asm(".global pthread_attr_destroy\n"
    ".type pthread_attr_destroy @function\n"
    "pthread_attr_destroy:\n");

asm(".global pthread_attr_get_np\n"
    ".type pthread_attr_get_np @function\n"
    "pthread_attr_get_np:\n");

asm(".global pthread_attr_getaffinity_np\n"
    ".type pthread_attr_getaffinity_np @function\n"
    "pthread_attr_getaffinity_np:\n");

asm(".global pthread_attr_getdetachstate\n"
    ".type pthread_attr_getdetachstate @function\n"
    "pthread_attr_getdetachstate:\n");

asm(".global pthread_attr_getguardsize\n"
    ".type pthread_attr_getguardsize @function\n"
    "pthread_attr_getguardsize:\n");

asm(".global pthread_attr_getinheritsched\n"
    ".type pthread_attr_getinheritsched @function\n"
    "pthread_attr_getinheritsched:\n");

asm(".global pthread_attr_getschedparam\n"
    ".type pthread_attr_getschedparam @function\n"
    "pthread_attr_getschedparam:\n");

asm(".global pthread_attr_getschedpolicy\n"
    ".type pthread_attr_getschedpolicy @function\n"
    "pthread_attr_getschedpolicy:\n");

asm(".global pthread_attr_getscope\n"
    ".type pthread_attr_getscope @function\n"
    "pthread_attr_getscope:\n");

asm(".global pthread_attr_getsolosched_np\n"
    ".type pthread_attr_getsolosched_np @function\n"
    "pthread_attr_getsolosched_np:\n");

asm(".global pthread_attr_getstack\n"
    ".type pthread_attr_getstack @function\n"
    "pthread_attr_getstack:\n");

asm(".global pthread_attr_getstackaddr\n"
    ".type pthread_attr_getstackaddr @function\n"
    "pthread_attr_getstackaddr:\n");

asm(".global pthread_attr_getstacksize\n"
    ".type pthread_attr_getstacksize @function\n"
    "pthread_attr_getstacksize:\n");

asm(".global pthread_attr_init\n"
    ".type pthread_attr_init @function\n"
    "pthread_attr_init:\n");

asm(".global pthread_attr_setaffinity_np\n"
    ".type pthread_attr_setaffinity_np @function\n"
    "pthread_attr_setaffinity_np:\n");

asm(".global pthread_attr_setcreatesuspend_np\n"
    ".type pthread_attr_setcreatesuspend_np @function\n"
    "pthread_attr_setcreatesuspend_np:\n");

asm(".global pthread_attr_setdetachstate\n"
    ".type pthread_attr_setdetachstate @function\n"
    "pthread_attr_setdetachstate:\n");

asm(".global pthread_attr_setguardsize\n"
    ".type pthread_attr_setguardsize @function\n"
    "pthread_attr_setguardsize:\n");

asm(".global pthread_attr_setinheritsched\n"
    ".type pthread_attr_setinheritsched @function\n"
    "pthread_attr_setinheritsched:\n");

asm(".global pthread_attr_setschedparam\n"
    ".type pthread_attr_setschedparam @function\n"
    "pthread_attr_setschedparam:\n");

asm(".global pthread_attr_setschedpolicy\n"
    ".type pthread_attr_setschedpolicy @function\n"
    "pthread_attr_setschedpolicy:\n");

asm(".global pthread_attr_setscope\n"
    ".type pthread_attr_setscope @function\n"
    "pthread_attr_setscope:\n");

asm(".global pthread_attr_setsolosched_np\n"
    ".type pthread_attr_setsolosched_np @function\n"
    "pthread_attr_setsolosched_np:\n");

asm(".global pthread_attr_setstack\n"
    ".type pthread_attr_setstack @function\n"
    "pthread_attr_setstack:\n");

asm(".global pthread_attr_setstackaddr\n"
    ".type pthread_attr_setstackaddr @function\n"
    "pthread_attr_setstackaddr:\n");

asm(".global pthread_attr_setstacksize\n"
    ".type pthread_attr_setstacksize @function\n"
    "pthread_attr_setstacksize:\n");

asm(".global pthread_barrier_destroy\n"
    ".type pthread_barrier_destroy @function\n"
    "pthread_barrier_destroy:\n");

asm(".global pthread_barrier_init\n"
    ".type pthread_barrier_init @function\n"
    "pthread_barrier_init:\n");

asm(".global pthread_barrier_setname_np\n"
    ".type pthread_barrier_setname_np @function\n"
    "pthread_barrier_setname_np:\n");

asm(".global pthread_barrier_wait\n"
    ".type pthread_barrier_wait @function\n"
    "pthread_barrier_wait:\n");

asm(".global pthread_barrierattr_destroy\n"
    ".type pthread_barrierattr_destroy @function\n"
    "pthread_barrierattr_destroy:\n");

asm(".global pthread_barrierattr_getpshared\n"
    ".type pthread_barrierattr_getpshared @function\n"
    "pthread_barrierattr_getpshared:\n");

asm(".global pthread_barrierattr_init\n"
    ".type pthread_barrierattr_init @function\n"
    "pthread_barrierattr_init:\n");

asm(".global pthread_barrierattr_setpshared\n"
    ".type pthread_barrierattr_setpshared @function\n"
    "pthread_barrierattr_setpshared:\n");

asm(".global pthread_cancel\n"
    ".type pthread_cancel @function\n"
    "pthread_cancel:\n");

asm(".global pthread_cleanup_pop\n"
    ".type pthread_cleanup_pop @function\n"
    "pthread_cleanup_pop:\n");

asm(".global pthread_cleanup_push\n"
    ".type pthread_cleanup_push @function\n"
    "pthread_cleanup_push:\n");

asm(".global pthread_cond_broadcast\n"
    ".type pthread_cond_broadcast @function\n"
    "pthread_cond_broadcast:\n");

asm(".global pthread_cond_destroy\n"
    ".type pthread_cond_destroy @function\n"
    "pthread_cond_destroy:\n");

asm(".global pthread_cond_init\n"
    ".type pthread_cond_init @function\n"
    "pthread_cond_init:\n");

asm(".global pthread_cond_reltimedwait_np\n"
    ".type pthread_cond_reltimedwait_np @function\n"
    "pthread_cond_reltimedwait_np:\n");

asm(".global pthread_cond_setname_np\n"
    ".type pthread_cond_setname_np @function\n"
    "pthread_cond_setname_np:\n");

asm(".global pthread_cond_signal\n"
    ".type pthread_cond_signal @function\n"
    "pthread_cond_signal:\n");

asm(".global pthread_cond_signalto_np\n"
    ".type pthread_cond_signalto_np @function\n"
    "pthread_cond_signalto_np:\n");

asm(".global pthread_cond_timedwait\n"
    ".type pthread_cond_timedwait @function\n"
    "pthread_cond_timedwait:\n");

asm(".global pthread_cond_wait\n"
    ".type pthread_cond_wait @function\n"
    "pthread_cond_wait:\n");

asm(".global pthread_condattr_destroy\n"
    ".type pthread_condattr_destroy @function\n"
    "pthread_condattr_destroy:\n");

asm(".global pthread_condattr_getclock\n"
    ".type pthread_condattr_getclock @function\n"
    "pthread_condattr_getclock:\n");

asm(".global pthread_condattr_getpshared\n"
    ".type pthread_condattr_getpshared @function\n"
    "pthread_condattr_getpshared:\n");

asm(".global pthread_condattr_init\n"
    ".type pthread_condattr_init @function\n"
    "pthread_condattr_init:\n");

asm(".global pthread_condattr_setclock\n"
    ".type pthread_condattr_setclock @function\n"
    "pthread_condattr_setclock:\n");

asm(".global pthread_condattr_setpshared\n"
    ".type pthread_condattr_setpshared @function\n"
    "pthread_condattr_setpshared:\n");

asm(".global pthread_create\n"
    ".type pthread_create @function\n"
    "pthread_create:\n");

asm(".global pthread_create_name_np\n"
    ".type pthread_create_name_np @function\n"
    "pthread_create_name_np:\n");

asm(".global pthread_detach\n"
    ".type pthread_detach @function\n"
    "pthread_detach:\n");

asm(".global pthread_equal\n"
    ".type pthread_equal @function\n"
    "pthread_equal:\n");

asm(".global pthread_exit\n"
    ".type pthread_exit @function\n"
    "pthread_exit:\n");

asm(".global pthread_get_specificarray_np\n"
    ".type pthread_get_specificarray_np @function\n"
    "pthread_get_specificarray_np:\n");

asm(".global pthread_get_user_context_np\n"
    ".type pthread_get_user_context_np @function\n"
    "pthread_get_user_context_np:\n");

asm(".global pthread_getaffinity_np\n"
    ".type pthread_getaffinity_np @function\n"
    "pthread_getaffinity_np:\n");

asm(".global pthread_getconcurrency\n"
    ".type pthread_getconcurrency @function\n"
    "pthread_getconcurrency:\n");

asm(".global pthread_getcpuclockid\n"
    ".type pthread_getcpuclockid @function\n"
    "pthread_getcpuclockid:\n");

asm(".global pthread_getname_np\n"
    ".type pthread_getname_np @function\n"
    "pthread_getname_np:\n");

asm(".global pthread_getprio\n"
    ".type pthread_getprio @function\n"
    "pthread_getprio:\n");

asm(".global pthread_getschedparam\n"
    ".type pthread_getschedparam @function\n"
    "pthread_getschedparam:\n");

asm(".global pthread_getspecific\n"
    ".type pthread_getspecific @function\n"
    "pthread_getspecific:\n");

asm(".global pthread_getstack_np\n"
    ".type pthread_getstack_np @function\n"
    "pthread_getstack_np:\n");

asm(".global pthread_getthreadid_np\n"
    ".type pthread_getthreadid_np @function\n"
    "pthread_getthreadid_np:\n");

asm(".global pthread_join\n"
    ".type pthread_join @function\n"
    "pthread_join:\n");

asm(".global pthread_key_create\n"
    ".type pthread_key_create @function\n"
    "pthread_key_create:\n");

asm(".global pthread_key_delete\n"
    ".type pthread_key_delete @function\n"
    "pthread_key_delete:\n");

asm(".global pthread_kill\n"
    ".type pthread_kill @function\n"
    "pthread_kill:\n");

asm(".global pthread_main_np\n"
    ".type pthread_main_np @function\n"
    "pthread_main_np:\n");

asm(".global pthread_multi_np\n"
    ".type pthread_multi_np @function\n"
    "pthread_multi_np:\n");

asm(".global pthread_mutex_destroy\n"
    ".type pthread_mutex_destroy @function\n"
    "pthread_mutex_destroy:\n");

asm(".global pthread_mutex_getprioceiling\n"
    ".type pthread_mutex_getprioceiling @function\n"
    "pthread_mutex_getprioceiling:\n");

asm(".global pthread_mutex_getspinloops_np\n"
    ".type pthread_mutex_getspinloops_np @function\n"
    "pthread_mutex_getspinloops_np:\n");

asm(".global pthread_mutex_getyieldloops_np\n"
    ".type pthread_mutex_getyieldloops_np @function\n"
    "pthread_mutex_getyieldloops_np:\n");

asm(".global pthread_mutex_init\n"
    ".type pthread_mutex_init @function\n"
    "pthread_mutex_init:\n");

asm(".global pthread_mutex_init_for_mono\n"
    ".type pthread_mutex_init_for_mono @function\n"
    "pthread_mutex_init_for_mono:\n");

asm(".global pthread_mutex_isowned_np\n"
    ".type pthread_mutex_isowned_np @function\n"
    "pthread_mutex_isowned_np:\n");

asm(".global pthread_mutex_lock\n"
    ".type pthread_mutex_lock @function\n"
    "pthread_mutex_lock:\n");

asm(".global pthread_mutex_reltimedlock_np\n"
    ".type pthread_mutex_reltimedlock_np @function\n"
    "pthread_mutex_reltimedlock_np:\n");

asm(".global pthread_mutex_setname_np\n"
    ".type pthread_mutex_setname_np @function\n"
    "pthread_mutex_setname_np:\n");

asm(".global pthread_mutex_setprioceiling\n"
    ".type pthread_mutex_setprioceiling @function\n"
    "pthread_mutex_setprioceiling:\n");

asm(".global pthread_mutex_setspinloops_np\n"
    ".type pthread_mutex_setspinloops_np @function\n"
    "pthread_mutex_setspinloops_np:\n");

asm(".global pthread_mutex_setyieldloops_np\n"
    ".type pthread_mutex_setyieldloops_np @function\n"
    "pthread_mutex_setyieldloops_np:\n");

asm(".global pthread_mutex_timedlock\n"
    ".type pthread_mutex_timedlock @function\n"
    "pthread_mutex_timedlock:\n");

asm(".global pthread_mutex_trylock\n"
    ".type pthread_mutex_trylock @function\n"
    "pthread_mutex_trylock:\n");

asm(".global pthread_mutex_unlock\n"
    ".type pthread_mutex_unlock @function\n"
    "pthread_mutex_unlock:\n");

asm(".global pthread_mutexattr_destroy\n"
    ".type pthread_mutexattr_destroy @function\n"
    "pthread_mutexattr_destroy:\n");

asm(".global pthread_mutexattr_getgen_np\n"
    ".type pthread_mutexattr_getgen_np @function\n"
    "pthread_mutexattr_getgen_np:\n");

asm(".global pthread_mutexattr_getkind_np\n"
    ".type pthread_mutexattr_getkind_np @function\n"
    "pthread_mutexattr_getkind_np:\n");

asm(".global pthread_mutexattr_getprioceiling\n"
    ".type pthread_mutexattr_getprioceiling @function\n"
    "pthread_mutexattr_getprioceiling:\n");

asm(".global pthread_mutexattr_getprotocol\n"
    ".type pthread_mutexattr_getprotocol @function\n"
    "pthread_mutexattr_getprotocol:\n");

asm(".global pthread_mutexattr_getpshared\n"
    ".type pthread_mutexattr_getpshared @function\n"
    "pthread_mutexattr_getpshared:\n");

asm(".global pthread_mutexattr_gettype\n"
    ".type pthread_mutexattr_gettype @function\n"
    "pthread_mutexattr_gettype:\n");

asm(".global pthread_mutexattr_init\n"
    ".type pthread_mutexattr_init @function\n"
    "pthread_mutexattr_init:\n");

asm(".global pthread_mutexattr_setgen_np\n"
    ".type pthread_mutexattr_setgen_np @function\n"
    "pthread_mutexattr_setgen_np:\n");

asm(".global pthread_mutexattr_setkind_np\n"
    ".type pthread_mutexattr_setkind_np @function\n"
    "pthread_mutexattr_setkind_np:\n");

asm(".global pthread_mutexattr_setprioceiling\n"
    ".type pthread_mutexattr_setprioceiling @function\n"
    "pthread_mutexattr_setprioceiling:\n");

asm(".global pthread_mutexattr_setprotocol\n"
    ".type pthread_mutexattr_setprotocol @function\n"
    "pthread_mutexattr_setprotocol:\n");

asm(".global pthread_mutexattr_setpshared\n"
    ".type pthread_mutexattr_setpshared @function\n"
    "pthread_mutexattr_setpshared:\n");

asm(".global pthread_mutexattr_settype\n"
    ".type pthread_mutexattr_settype @function\n"
    "pthread_mutexattr_settype:\n");

asm(".global pthread_once\n"
    ".type pthread_once @function\n"
    "pthread_once:\n");

asm(".global pthread_rename_np\n"
    ".type pthread_rename_np @function\n"
    "pthread_rename_np:\n");

asm(".global pthread_resume_all_np\n"
    ".type pthread_resume_all_np @function\n"
    "pthread_resume_all_np:\n");

asm(".global pthread_resume_np\n"
    ".type pthread_resume_np @function\n"
    "pthread_resume_np:\n");

asm(".global pthread_resume_user_context_np\n"
    ".type pthread_resume_user_context_np @function\n"
    "pthread_resume_user_context_np:\n");

asm(".global pthread_rwlock_destroy\n"
    ".type pthread_rwlock_destroy @function\n"
    "pthread_rwlock_destroy:\n");

asm(".global pthread_rwlock_init\n"
    ".type pthread_rwlock_init @function\n"
    "pthread_rwlock_init:\n");

asm(".global pthread_rwlock_rdlock\n"
    ".type pthread_rwlock_rdlock @function\n"
    "pthread_rwlock_rdlock:\n");

asm(".global pthread_rwlock_reltimedrdlock_np\n"
    ".type pthread_rwlock_reltimedrdlock_np @function\n"
    "pthread_rwlock_reltimedrdlock_np:\n");

asm(".global pthread_rwlock_reltimedwrlock_np\n"
    ".type pthread_rwlock_reltimedwrlock_np @function\n"
    "pthread_rwlock_reltimedwrlock_np:\n");

asm(".global pthread_rwlock_setname_np\n"
    ".type pthread_rwlock_setname_np @function\n"
    "pthread_rwlock_setname_np:\n");

asm(".global pthread_rwlock_timedrdlock\n"
    ".type pthread_rwlock_timedrdlock @function\n"
    "pthread_rwlock_timedrdlock:\n");

asm(".global pthread_rwlock_timedwrlock\n"
    ".type pthread_rwlock_timedwrlock @function\n"
    "pthread_rwlock_timedwrlock:\n");

asm(".global pthread_rwlock_tryrdlock\n"
    ".type pthread_rwlock_tryrdlock @function\n"
    "pthread_rwlock_tryrdlock:\n");

asm(".global pthread_rwlock_trywrlock\n"
    ".type pthread_rwlock_trywrlock @function\n"
    "pthread_rwlock_trywrlock:\n");

asm(".global pthread_rwlock_unlock\n"
    ".type pthread_rwlock_unlock @function\n"
    "pthread_rwlock_unlock:\n");

asm(".global pthread_rwlock_wrlock\n"
    ".type pthread_rwlock_wrlock @function\n"
    "pthread_rwlock_wrlock:\n");

asm(".global pthread_rwlockattr_destroy\n"
    ".type pthread_rwlockattr_destroy @function\n"
    "pthread_rwlockattr_destroy:\n");

asm(".global pthread_rwlockattr_getpshared\n"
    ".type pthread_rwlockattr_getpshared @function\n"
    "pthread_rwlockattr_getpshared:\n");

asm(".global pthread_rwlockattr_gettype_np\n"
    ".type pthread_rwlockattr_gettype_np @function\n"
    "pthread_rwlockattr_gettype_np:\n");

asm(".global pthread_rwlockattr_init\n"
    ".type pthread_rwlockattr_init @function\n"
    "pthread_rwlockattr_init:\n");

asm(".global pthread_rwlockattr_setpshared\n"
    ".type pthread_rwlockattr_setpshared @function\n"
    "pthread_rwlockattr_setpshared:\n");

asm(".global pthread_rwlockattr_settype_np\n"
    ".type pthread_rwlockattr_settype_np @function\n"
    "pthread_rwlockattr_settype_np:\n");

asm(".global pthread_self\n"
    ".type pthread_self @function\n"
    "pthread_self:\n");

asm(".global pthread_set_defaultstacksize_np\n"
    ".type pthread_set_defaultstacksize_np @function\n"
    "pthread_set_defaultstacksize_np:\n");

asm(".global pthread_set_name_np\n"
    ".type pthread_set_name_np @function\n"
    "pthread_set_name_np:\n");

asm(".global pthread_set_user_context_np\n"
    ".type pthread_set_user_context_np @function\n"
    "pthread_set_user_context_np:\n");

asm(".global pthread_setaffinity_np\n"
    ".type pthread_setaffinity_np @function\n"
    "pthread_setaffinity_np:\n");

asm(".global pthread_setcancelstate\n"
    ".type pthread_setcancelstate @function\n"
    "pthread_setcancelstate:\n");

asm(".global pthread_setcanceltype\n"
    ".type pthread_setcanceltype @function\n"
    "pthread_setcanceltype:\n");

asm(".global pthread_setconcurrency\n"
    ".type pthread_setconcurrency @function\n"
    "pthread_setconcurrency:\n");

asm(".global pthread_setprio\n"
    ".type pthread_setprio @function\n"
    "pthread_setprio:\n");

asm(".global pthread_setschedparam\n"
    ".type pthread_setschedparam @function\n"
    "pthread_setschedparam:\n");

asm(".global pthread_setspecific\n"
    ".type pthread_setspecific @function\n"
    "pthread_setspecific:\n");

asm(".global pthread_sigmask\n"
    ".type pthread_sigmask @function\n"
    "pthread_sigmask:\n");

asm(".global pthread_single_np\n"
    ".type pthread_single_np @function\n"
    "pthread_single_np:\n");

asm(".global pthread_spin_destroy\n"
    ".type pthread_spin_destroy @function\n"
    "pthread_spin_destroy:\n");

asm(".global pthread_spin_init\n"
    ".type pthread_spin_init @function\n"
    "pthread_spin_init:\n");

asm(".global pthread_spin_lock\n"
    ".type pthread_spin_lock @function\n"
    "pthread_spin_lock:\n");

asm(".global pthread_spin_trylock\n"
    ".type pthread_spin_trylock @function\n"
    "pthread_spin_trylock:\n");

asm(".global pthread_spin_unlock\n"
    ".type pthread_spin_unlock @function\n"
    "pthread_spin_unlock:\n");

asm(".global pthread_suspend_all_np\n"
    ".type pthread_suspend_all_np @function\n"
    "pthread_suspend_all_np:\n");

asm(".global pthread_suspend_np\n"
    ".type pthread_suspend_np @function\n"
    "pthread_suspend_np:\n");

asm(".global pthread_suspend_user_context_np\n"
    ".type pthread_suspend_user_context_np @function\n"
    "pthread_suspend_user_context_np:\n");

asm(".global pthread_switch_add_np\n"
    ".type pthread_switch_add_np @function\n"
    "pthread_switch_add_np:\n");

asm(".global pthread_switch_delete_np\n"
    ".type pthread_switch_delete_np @function\n"
    "pthread_switch_delete_np:\n");

asm(".global pthread_testcancel\n"
    ".type pthread_testcancel @function\n"
    "pthread_testcancel:\n");

asm(".global pthread_timedjoin_np\n"
    ".type pthread_timedjoin_np @function\n"
    "pthread_timedjoin_np:\n");

asm(".global pthread_yield\n"
    ".type pthread_yield @function\n"
    "pthread_yield:\n");
