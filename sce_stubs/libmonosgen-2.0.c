
asm(".global coil_dlclose\n"
    ".type coil_dlclose @function\n"
    "coil_dlclose:\n");

asm(".global coil_dlopen_native\n"
    ".type coil_dlopen_native @function\n"
    "coil_dlopen_native:\n");

asm(".global coil_dlsym\n"
    ".type coil_dlsym @function\n"
    "coil_dlsym:\n");

asm(".global coil_load_module_internal\n"
    ".type coil_load_module_internal @function\n"
    "coil_load_module_internal:\n");

asm(".global coil_mkstemp\n"
    ".type coil_mkstemp @function\n"
    "coil_mkstemp:\n");

asm(".global coil_mspace_calloc\n"
    ".type coil_mspace_calloc @function\n"
    "coil_mspace_calloc:\n");

asm(".global coil_mspace_free\n"
    ".type coil_mspace_free @function\n"
    "coil_mspace_free:\n");

asm(".global coil_mspace_malloc\n"
    ".type coil_mspace_malloc @function\n"
    "coil_mspace_malloc:\n");

asm(".global coil_mspace_realloc\n"
    ".type coil_mspace_realloc @function\n"
    "coil_mspace_realloc:\n");

asm(".global coil_netctrl_get_str\n"
    ".type coil_netctrl_get_str @function\n"
    "coil_netctrl_get_str:\n");

asm(".global coil_netctrl_init\n"
    ".type coil_netctrl_init @function\n"
    "coil_netctrl_init:\n");

asm(".global coil_pclose\n"
    ".type coil_pclose @function\n"
    "coil_pclose:\n");

asm(".global coil_popen\n"
    ".type coil_popen @function\n"
    "coil_popen:\n");

asm(".global mini_get_debug_options\n"
    ".type mini_get_debug_options @function\n"
    "mini_get_debug_options:\n");

asm(".global mono_add_internal_call\n"
    ".type mono_add_internal_call @function\n"
    "mono_add_internal_call:\n");

asm(".global mono_aot_get_method\n"
    ".type mono_aot_get_method @function\n"
    "mono_aot_get_method:\n");

asm(".global mono_aot_register_module\n"
    ".type mono_aot_register_module @function\n"
    "mono_aot_register_module:\n");

asm(".global mono_array_addr_with_size\n"
    ".type mono_array_addr_with_size @function\n"
    "mono_array_addr_with_size:\n");

asm(".global mono_array_class_get\n"
    ".type mono_array_class_get @function\n"
    "mono_array_class_get:\n");

asm(".global mono_array_clone\n"
    ".type mono_array_clone @function\n"
    "mono_array_clone:\n");

asm(".global mono_array_element_size\n"
    ".type mono_array_element_size @function\n"
    "mono_array_element_size:\n");

asm(".global mono_array_length\n"
    ".type mono_array_length @function\n"
    "mono_array_length:\n");

asm(".global mono_array_new\n"
    ".type mono_array_new @function\n"
    "mono_array_new:\n");

asm(".global mono_array_new_full\n"
    ".type mono_array_new_full @function\n"
    "mono_array_new_full:\n");

asm(".global mono_array_new_specific\n"
    ".type mono_array_new_specific @function\n"
    "mono_array_new_specific:\n");

asm(".global mono_assemblies_cleanup\n"
    ".type mono_assemblies_cleanup @function\n"
    "mono_assemblies_cleanup:\n");

asm(".global mono_assemblies_init\n"
    ".type mono_assemblies_init @function\n"
    "mono_assemblies_init:\n");

asm(".global mono_assembly_addref\n"
    ".type mono_assembly_addref @function\n"
    "mono_assembly_addref:\n");

asm(".global mono_assembly_close\n"
    ".type mono_assembly_close @function\n"
    "mono_assembly_close:\n");

asm(".global mono_assembly_fill_assembly_name\n"
    ".type mono_assembly_fill_assembly_name @function\n"
    "mono_assembly_fill_assembly_name:\n");

asm(".global mono_assembly_foreach\n"
    ".type mono_assembly_foreach @function\n"
    "mono_assembly_foreach:\n");

asm(".global mono_assembly_get_assemblyref\n"
    ".type mono_assembly_get_assemblyref @function\n"
    "mono_assembly_get_assemblyref:\n");

asm(".global mono_assembly_get_image\n"
    ".type mono_assembly_get_image @function\n"
    "mono_assembly_get_image:\n");

asm(".global mono_assembly_get_main\n"
    ".type mono_assembly_get_main @function\n"
    "mono_assembly_get_main:\n");

asm(".global mono_assembly_get_name\n"
    ".type mono_assembly_get_name @function\n"
    "mono_assembly_get_name:\n");

asm(".global mono_assembly_get_object\n"
    ".type mono_assembly_get_object @function\n"
    "mono_assembly_get_object:\n");

asm(".global mono_assembly_getrootdir\n"
    ".type mono_assembly_getrootdir @function\n"
    "mono_assembly_getrootdir:\n");

asm(".global mono_assembly_invoke_load_hook\n"
    ".type mono_assembly_invoke_load_hook @function\n"
    "mono_assembly_invoke_load_hook:\n");

asm(".global mono_assembly_invoke_search_hook\n"
    ".type mono_assembly_invoke_search_hook @function\n"
    "mono_assembly_invoke_search_hook:\n");

asm(".global mono_assembly_load\n"
    ".type mono_assembly_load @function\n"
    "mono_assembly_load:\n");

asm(".global mono_assembly_load_from\n"
    ".type mono_assembly_load_from @function\n"
    "mono_assembly_load_from:\n");

asm(".global mono_assembly_load_from_full\n"
    ".type mono_assembly_load_from_full @function\n"
    "mono_assembly_load_from_full:\n");

asm(".global mono_assembly_load_full\n"
    ".type mono_assembly_load_full @function\n"
    "mono_assembly_load_full:\n");

asm(".global mono_assembly_load_module\n"
    ".type mono_assembly_load_module @function\n"
    "mono_assembly_load_module:\n");

asm(".global mono_assembly_load_reference\n"
    ".type mono_assembly_load_reference @function\n"
    "mono_assembly_load_reference:\n");

asm(".global mono_assembly_load_references\n"
    ".type mono_assembly_load_references @function\n"
    "mono_assembly_load_references:\n");

asm(".global mono_assembly_load_with_partial_name\n"
    ".type mono_assembly_load_with_partial_name @function\n"
    "mono_assembly_load_with_partial_name:\n");

asm(".global mono_assembly_loaded\n"
    ".type mono_assembly_loaded @function\n"
    "mono_assembly_loaded:\n");

asm(".global mono_assembly_loaded_full\n"
    ".type mono_assembly_loaded_full @function\n"
    "mono_assembly_loaded_full:\n");

asm(".global mono_assembly_name_free\n"
    ".type mono_assembly_name_free @function\n"
    "mono_assembly_name_free:\n");

asm(".global mono_assembly_name_get_culture\n"
    ".type mono_assembly_name_get_culture @function\n"
    "mono_assembly_name_get_culture:\n");

asm(".global mono_assembly_name_get_name\n"
    ".type mono_assembly_name_get_name @function\n"
    "mono_assembly_name_get_name:\n");

asm(".global mono_assembly_name_get_pubkeytoken\n"
    ".type mono_assembly_name_get_pubkeytoken @function\n"
    "mono_assembly_name_get_pubkeytoken:\n");

asm(".global mono_assembly_name_get_version\n"
    ".type mono_assembly_name_get_version @function\n"
    "mono_assembly_name_get_version:\n");

asm(".global mono_assembly_name_new\n"
    ".type mono_assembly_name_new @function\n"
    "mono_assembly_name_new:\n");

asm(".global mono_assembly_names_equal\n"
    ".type mono_assembly_names_equal @function\n"
    "mono_assembly_names_equal:\n");

asm(".global mono_assembly_open\n"
    ".type mono_assembly_open @function\n"
    "mono_assembly_open:\n");

asm(".global mono_assembly_open_full\n"
    ".type mono_assembly_open_full @function\n"
    "mono_assembly_open_full:\n");

asm(".global mono_assembly_set_main\n"
    ".type mono_assembly_set_main @function\n"
    "mono_assembly_set_main:\n");

asm(".global mono_assembly_setrootdir\n"
    ".type mono_assembly_setrootdir @function\n"
    "mono_assembly_setrootdir:\n");

asm(".global mono_bitset_alloc_size\n"
    ".type mono_bitset_alloc_size @function\n"
    "mono_bitset_alloc_size:\n");

asm(".global mono_bitset_clear\n"
    ".type mono_bitset_clear @function\n"
    "mono_bitset_clear:\n");

asm(".global mono_bitset_clear_all\n"
    ".type mono_bitset_clear_all @function\n"
    "mono_bitset_clear_all:\n");

asm(".global mono_bitset_clone\n"
    ".type mono_bitset_clone @function\n"
    "mono_bitset_clone:\n");

asm(".global mono_bitset_copyto\n"
    ".type mono_bitset_copyto @function\n"
    "mono_bitset_copyto:\n");

asm(".global mono_bitset_count\n"
    ".type mono_bitset_count @function\n"
    "mono_bitset_count:\n");

asm(".global mono_bitset_equal\n"
    ".type mono_bitset_equal @function\n"
    "mono_bitset_equal:\n");

asm(".global mono_bitset_find_first\n"
    ".type mono_bitset_find_first @function\n"
    "mono_bitset_find_first:\n");

asm(".global mono_bitset_find_first_unset\n"
    ".type mono_bitset_find_first_unset @function\n"
    "mono_bitset_find_first_unset:\n");

asm(".global mono_bitset_find_last\n"
    ".type mono_bitset_find_last @function\n"
    "mono_bitset_find_last:\n");

asm(".global mono_bitset_find_start\n"
    ".type mono_bitset_find_start @function\n"
    "mono_bitset_find_start:\n");

asm(".global mono_bitset_foreach\n"
    ".type mono_bitset_foreach @function\n"
    "mono_bitset_foreach:\n");

asm(".global mono_bitset_free\n"
    ".type mono_bitset_free @function\n"
    "mono_bitset_free:\n");

asm(".global mono_bitset_intersection\n"
    ".type mono_bitset_intersection @function\n"
    "mono_bitset_intersection:\n");

asm(".global mono_bitset_intersection_2\n"
    ".type mono_bitset_intersection_2 @function\n"
    "mono_bitset_intersection_2:\n");

asm(".global mono_bitset_invert\n"
    ".type mono_bitset_invert @function\n"
    "mono_bitset_invert:\n");

asm(".global mono_bitset_mem_new\n"
    ".type mono_bitset_mem_new @function\n"
    "mono_bitset_mem_new:\n");

asm(".global mono_bitset_new\n"
    ".type mono_bitset_new @function\n"
    "mono_bitset_new:\n");

asm(".global mono_bitset_set\n"
    ".type mono_bitset_set @function\n"
    "mono_bitset_set:\n");

asm(".global mono_bitset_set_all\n"
    ".type mono_bitset_set_all @function\n"
    "mono_bitset_set_all:\n");

asm(".global mono_bitset_size\n"
    ".type mono_bitset_size @function\n"
    "mono_bitset_size:\n");

asm(".global mono_bitset_sub\n"
    ".type mono_bitset_sub @function\n"
    "mono_bitset_sub:\n");

asm(".global mono_bitset_test\n"
    ".type mono_bitset_test @function\n"
    "mono_bitset_test:\n");

asm(".global mono_bitset_test_bulk\n"
    ".type mono_bitset_test_bulk @function\n"
    "mono_bitset_test_bulk:\n");

asm(".global mono_bitset_union\n"
    ".type mono_bitset_union @function\n"
    "mono_bitset_union:\n");

asm(".global mono_bounded_array_class_get\n"
    ".type mono_bounded_array_class_get @function\n"
    "mono_bounded_array_class_get:\n");

asm(".global mono_breakpoint_clean_code\n"
    ".type mono_breakpoint_clean_code @function\n"
    "mono_breakpoint_clean_code:\n");

asm(".global mono_check_corlib_version\n"
    ".type mono_check_corlib_version @function\n"
    "mono_check_corlib_version:\n");

asm(".global mono_class_array_element_size\n"
    ".type mono_class_array_element_size @function\n"
    "mono_class_array_element_size:\n");

asm(".global mono_class_data_size\n"
    ".type mono_class_data_size @function\n"
    "mono_class_data_size:\n");

asm(".global mono_class_describe_statics\n"
    ".type mono_class_describe_statics @function\n"
    "mono_class_describe_statics:\n");

asm(".global mono_class_enum_basetype\n"
    ".type mono_class_enum_basetype @function\n"
    "mono_class_enum_basetype:\n");

asm(".global mono_class_from_generic_parameter\n"
    ".type mono_class_from_generic_parameter @function\n"
    "mono_class_from_generic_parameter:\n");

asm(".global mono_class_from_mono_type\n"
    ".type mono_class_from_mono_type @function\n"
    "mono_class_from_mono_type:\n");

asm(".global mono_class_from_name\n"
    ".type mono_class_from_name @function\n"
    "mono_class_from_name:\n");

asm(".global mono_class_from_name_case\n"
    ".type mono_class_from_name_case @function\n"
    "mono_class_from_name_case:\n");

asm(".global mono_class_from_typeref\n"
    ".type mono_class_from_typeref @function\n"
    "mono_class_from_typeref:\n");

asm(".global mono_class_from_typeref_checked\n"
    ".type mono_class_from_typeref_checked @function\n"
    "mono_class_from_typeref_checked:\n");

asm(".global mono_class_get\n"
    ".type mono_class_get @function\n"
    "mono_class_get:\n");

asm(".global mono_class_get_byref_type\n"
    ".type mono_class_get_byref_type @function\n"
    "mono_class_get_byref_type:\n");

asm(".global mono_class_get_element_class\n"
    ".type mono_class_get_element_class @function\n"
    "mono_class_get_element_class:\n");

asm(".global mono_class_get_event_token\n"
    ".type mono_class_get_event_token @function\n"
    "mono_class_get_event_token:\n");

asm(".global mono_class_get_events\n"
    ".type mono_class_get_events @function\n"
    "mono_class_get_events:\n");

asm(".global mono_class_get_field\n"
    ".type mono_class_get_field @function\n"
    "mono_class_get_field:\n");

asm(".global mono_class_get_field_from_name\n"
    ".type mono_class_get_field_from_name @function\n"
    "mono_class_get_field_from_name:\n");

asm(".global mono_class_get_field_token\n"
    ".type mono_class_get_field_token @function\n"
    "mono_class_get_field_token:\n");

asm(".global mono_class_get_fields\n"
    ".type mono_class_get_fields @function\n"
    "mono_class_get_fields:\n");

asm(".global mono_class_get_flags\n"
    ".type mono_class_get_flags @function\n"
    "mono_class_get_flags:\n");

asm(".global mono_class_get_full\n"
    ".type mono_class_get_full @function\n"
    "mono_class_get_full:\n");

asm(".global mono_class_get_image\n"
    ".type mono_class_get_image @function\n"
    "mono_class_get_image:\n");

asm(".global mono_class_get_interfaces\n"
    ".type mono_class_get_interfaces @function\n"
    "mono_class_get_interfaces:\n");

asm(".global mono_class_get_method_from_name\n"
    ".type mono_class_get_method_from_name @function\n"
    "mono_class_get_method_from_name:\n");

asm(".global mono_class_get_method_from_name_flags\n"
    ".type mono_class_get_method_from_name_flags @function\n"
    "mono_class_get_method_from_name_flags:\n");

asm(".global mono_class_get_methods\n"
    ".type mono_class_get_methods @function\n"
    "mono_class_get_methods:\n");

asm(".global mono_class_get_name\n"
    ".type mono_class_get_name @function\n"
    "mono_class_get_name:\n");

asm(".global mono_class_get_namespace\n"
    ".type mono_class_get_namespace @function\n"
    "mono_class_get_namespace:\n");

asm(".global mono_class_get_nested_types\n"
    ".type mono_class_get_nested_types @function\n"
    "mono_class_get_nested_types:\n");

asm(".global mono_class_get_nesting_type\n"
    ".type mono_class_get_nesting_type @function\n"
    "mono_class_get_nesting_type:\n");

asm(".global mono_class_get_parent\n"
    ".type mono_class_get_parent @function\n"
    "mono_class_get_parent:\n");

asm(".global mono_class_get_properties\n"
    ".type mono_class_get_properties @function\n"
    "mono_class_get_properties:\n");

asm(".global mono_class_get_property_from_name\n"
    ".type mono_class_get_property_from_name @function\n"
    "mono_class_get_property_from_name:\n");

asm(".global mono_class_get_property_token\n"
    ".type mono_class_get_property_token @function\n"
    "mono_class_get_property_token:\n");

asm(".global mono_class_get_rank\n"
    ".type mono_class_get_rank @function\n"
    "mono_class_get_rank:\n");

asm(".global mono_class_get_type\n"
    ".type mono_class_get_type @function\n"
    "mono_class_get_type:\n");

asm(".global mono_class_get_type_token\n"
    ".type mono_class_get_type_token @function\n"
    "mono_class_get_type_token:\n");

asm(".global mono_class_implements_interface\n"
    ".type mono_class_implements_interface @function\n"
    "mono_class_implements_interface:\n");

asm(".global mono_class_inflate_generic_method\n"
    ".type mono_class_inflate_generic_method @function\n"
    "mono_class_inflate_generic_method:\n");

asm(".global mono_class_inflate_generic_type\n"
    ".type mono_class_inflate_generic_type @function\n"
    "mono_class_inflate_generic_type:\n");

asm(".global mono_class_init\n"
    ".type mono_class_init @function\n"
    "mono_class_init:\n");

asm(".global mono_class_instance_size\n"
    ".type mono_class_instance_size @function\n"
    "mono_class_instance_size:\n");

asm(".global mono_class_interface_offset\n"
    ".type mono_class_interface_offset @function\n"
    "mono_class_interface_offset:\n");

asm(".global mono_class_is_assignable_from\n"
    ".type mono_class_is_assignable_from @function\n"
    "mono_class_is_assignable_from:\n");

asm(".global mono_class_is_delegate\n"
    ".type mono_class_is_delegate @function\n"
    "mono_class_is_delegate:\n");

asm(".global mono_class_is_enum\n"
    ".type mono_class_is_enum @function\n"
    "mono_class_is_enum:\n");

asm(".global mono_class_is_subclass_of\n"
    ".type mono_class_is_subclass_of @function\n"
    "mono_class_is_subclass_of:\n");

asm(".global mono_class_is_valid_enum\n"
    ".type mono_class_is_valid_enum @function\n"
    "mono_class_is_valid_enum:\n");

asm(".global mono_class_is_valuetype\n"
    ".type mono_class_is_valuetype @function\n"
    "mono_class_is_valuetype:\n");

asm(".global mono_class_min_align\n"
    ".type mono_class_min_align @function\n"
    "mono_class_min_align:\n");

asm(".global mono_class_name_from_token\n"
    ".type mono_class_name_from_token @function\n"
    "mono_class_name_from_token:\n");

asm(".global mono_class_num_events\n"
    ".type mono_class_num_events @function\n"
    "mono_class_num_events:\n");

asm(".global mono_class_num_fields\n"
    ".type mono_class_num_fields @function\n"
    "mono_class_num_fields:\n");

asm(".global mono_class_num_methods\n"
    ".type mono_class_num_methods @function\n"
    "mono_class_num_methods:\n");

asm(".global mono_class_num_properties\n"
    ".type mono_class_num_properties @function\n"
    "mono_class_num_properties:\n");

asm(".global mono_class_value_size\n"
    ".type mono_class_value_size @function\n"
    "mono_class_value_size:\n");

asm(".global mono_class_vtable\n"
    ".type mono_class_vtable @function\n"
    "mono_class_vtable:\n");

asm(".global mono_cli_rva_image_map\n"
    ".type mono_cli_rva_image_map @function\n"
    "mono_cli_rva_image_map:\n");

asm(".global mono_code_manager_cleanup\n"
    ".type mono_code_manager_cleanup @function\n"
    "mono_code_manager_cleanup:\n");

asm(".global mono_code_manager_commit\n"
    ".type mono_code_manager_commit @function\n"
    "mono_code_manager_commit:\n");

asm(".global mono_code_manager_destroy\n"
    ".type mono_code_manager_destroy @function\n"
    "mono_code_manager_destroy:\n");

asm(".global mono_code_manager_init\n"
    ".type mono_code_manager_init @function\n"
    "mono_code_manager_init:\n");

asm(".global mono_code_manager_invalidate\n"
    ".type mono_code_manager_invalidate @function\n"
    "mono_code_manager_invalidate:\n");

asm(".global mono_code_manager_new\n"
    ".type mono_code_manager_new @function\n"
    "mono_code_manager_new:\n");

asm(".global mono_code_manager_new_dynamic\n"
    ".type mono_code_manager_new_dynamic @function\n"
    "mono_code_manager_new_dynamic:\n");

asm(".global mono_code_manager_reserve\n"
    ".type mono_code_manager_reserve @function\n"
    "mono_code_manager_reserve:\n");

asm(".global mono_code_manager_reserve_align\n"
    ".type mono_code_manager_reserve_align @function\n"
    "mono_code_manager_reserve_align:\n");

asm(".global mono_code_manager_set_read_only\n"
    ".type mono_code_manager_set_read_only @function\n"
    "mono_code_manager_set_read_only:\n");

asm(".global mono_code_manager_size\n"
    ".type mono_code_manager_size @function\n"
    "mono_code_manager_size:\n");

asm(".global mono_compile_method\n"
    ".type mono_compile_method @function\n"
    "mono_compile_method:\n");

asm(".global mono_conc_hashtable_destroy\n"
    ".type mono_conc_hashtable_destroy @function\n"
    "mono_conc_hashtable_destroy:\n");

asm(".global mono_conc_hashtable_foreach\n"
    ".type mono_conc_hashtable_foreach @function\n"
    "mono_conc_hashtable_foreach:\n");

asm(".global mono_conc_hashtable_insert\n"
    ".type mono_conc_hashtable_insert @function\n"
    "mono_conc_hashtable_insert:\n");

asm(".global mono_conc_hashtable_lookup\n"
    ".type mono_conc_hashtable_lookup @function\n"
    "mono_conc_hashtable_lookup:\n");

asm(".global mono_conc_hashtable_new\n"
    ".type mono_conc_hashtable_new @function\n"
    "mono_conc_hashtable_new:\n");

asm(".global mono_conc_hashtable_new_full\n"
    ".type mono_conc_hashtable_new_full @function\n"
    "mono_conc_hashtable_new_full:\n");

asm(".global mono_conc_hashtable_remove\n"
    ".type mono_conc_hashtable_remove @function\n"
    "mono_conc_hashtable_remove:\n");

asm(".global mono_config_cleanup\n"
    ".type mono_config_cleanup @function\n"
    "mono_config_cleanup:\n");

asm(".global mono_config_for_assembly\n"
    ".type mono_config_for_assembly @function\n"
    "mono_config_for_assembly:\n");

asm(".global mono_config_get_cpu\n"
    ".type mono_config_get_cpu @function\n"
    "mono_config_get_cpu:\n");

asm(".global mono_config_get_os\n"
    ".type mono_config_get_os @function\n"
    "mono_config_get_os:\n");

asm(".global mono_config_is_server_mode\n"
    ".type mono_config_is_server_mode @function\n"
    "mono_config_is_server_mode:\n");

asm(".global mono_config_parse\n"
    ".type mono_config_parse @function\n"
    "mono_config_parse:\n");

asm(".global mono_config_parse_memory\n"
    ".type mono_config_parse_memory @function\n"
    "mono_config_parse_memory:\n");

asm(".global mono_config_set_server_mode\n"
    ".type mono_config_set_server_mode @function\n"
    "mono_config_set_server_mode:\n");

asm(".global mono_config_string_for_assembly_file\n"
    ".type mono_config_string_for_assembly_file @function\n"
    "mono_config_string_for_assembly_file:\n");

asm(".global mono_context_get\n"
    ".type mono_context_get @function\n"
    "mono_context_get:\n");

asm(".global mono_context_get_desc\n"
    ".type mono_context_get_desc @function\n"
    "mono_context_get_desc:\n");

asm(".global mono_context_get_domain_id\n"
    ".type mono_context_get_domain_id @function\n"
    "mono_context_get_domain_id:\n");

asm(".global mono_context_get_id\n"
    ".type mono_context_get_id @function\n"
    "mono_context_get_id:\n");

asm(".global mono_context_init\n"
    ".type mono_context_init @function\n"
    "mono_context_init:\n");

asm(".global mono_context_set\n"
    ".type mono_context_set @function\n"
    "mono_context_set:\n");

asm(".global mono_counter_get_name\n"
    ".type mono_counter_get_name @function\n"
    "mono_counter_get_name:\n");

asm(".global mono_counter_get_section\n"
    ".type mono_counter_get_section @function\n"
    "mono_counter_get_section:\n");

asm(".global mono_counter_get_size\n"
    ".type mono_counter_get_size @function\n"
    "mono_counter_get_size:\n");

asm(".global mono_counter_get_type\n"
    ".type mono_counter_get_type @function\n"
    "mono_counter_get_type:\n");

asm(".global mono_counter_get_unit\n"
    ".type mono_counter_get_unit @function\n"
    "mono_counter_get_unit:\n");

asm(".global mono_counter_get_variance\n"
    ".type mono_counter_get_variance @function\n"
    "mono_counter_get_variance:\n");

asm(".global mono_counters_cleanup\n"
    ".type mono_counters_cleanup @function\n"
    "mono_counters_cleanup:\n");

asm(".global mono_counters_dump\n"
    ".type mono_counters_dump @function\n"
    "mono_counters_dump:\n");

asm(".global mono_counters_enable\n"
    ".type mono_counters_enable @function\n"
    "mono_counters_enable:\n");

asm(".global mono_counters_foreach\n"
    ".type mono_counters_foreach @function\n"
    "mono_counters_foreach:\n");

asm(".global mono_counters_init\n"
    ".type mono_counters_init @function\n"
    "mono_counters_init:\n");

asm(".global mono_counters_on_register\n"
    ".type mono_counters_on_register @function\n"
    "mono_counters_on_register:\n");

asm(".global mono_counters_register\n"
    ".type mono_counters_register @function\n"
    "mono_counters_register:\n");

asm(".global mono_counters_register_with_size\n"
    ".type mono_counters_register_with_size @function\n"
    "mono_counters_register_with_size:\n");

asm(".global mono_counters_sample\n"
    ".type mono_counters_sample @function\n"
    "mono_counters_sample:\n");

asm(".global mono_custom_attrs_construct\n"
    ".type mono_custom_attrs_construct @function\n"
    "mono_custom_attrs_construct:\n");

asm(".global mono_custom_attrs_free\n"
    ".type mono_custom_attrs_free @function\n"
    "mono_custom_attrs_free:\n");

asm(".global mono_custom_attrs_from_assembly\n"
    ".type mono_custom_attrs_from_assembly @function\n"
    "mono_custom_attrs_from_assembly:\n");

asm(".global mono_custom_attrs_from_class\n"
    ".type mono_custom_attrs_from_class @function\n"
    "mono_custom_attrs_from_class:\n");

asm(".global mono_custom_attrs_from_event\n"
    ".type mono_custom_attrs_from_event @function\n"
    "mono_custom_attrs_from_event:\n");

asm(".global mono_custom_attrs_from_field\n"
    ".type mono_custom_attrs_from_field @function\n"
    "mono_custom_attrs_from_field:\n");

asm(".global mono_custom_attrs_from_index\n"
    ".type mono_custom_attrs_from_index @function\n"
    "mono_custom_attrs_from_index:\n");

asm(".global mono_custom_attrs_from_method\n"
    ".type mono_custom_attrs_from_method @function\n"
    "mono_custom_attrs_from_method:\n");

asm(".global mono_custom_attrs_from_param\n"
    ".type mono_custom_attrs_from_param @function\n"
    "mono_custom_attrs_from_param:\n");

asm(".global mono_custom_attrs_from_property\n"
    ".type mono_custom_attrs_from_property @function\n"
    "mono_custom_attrs_from_property:\n");

asm(".global mono_custom_attrs_get_attr\n"
    ".type mono_custom_attrs_get_attr @function\n"
    "mono_custom_attrs_get_attr:\n");

asm(".global mono_custom_attrs_has_attr\n"
    ".type mono_custom_attrs_has_attr @function\n"
    "mono_custom_attrs_has_attr:\n");

asm(".global mono_debug_add_delegate_trampoline\n"
    ".type mono_debug_add_delegate_trampoline @function\n"
    "mono_debug_add_delegate_trampoline:\n");

asm(".global mono_debug_add_method\n"
    ".type mono_debug_add_method @function\n"
    "mono_debug_add_method:\n");

asm(".global mono_debug_cleanup\n"
    ".type mono_debug_cleanup @function\n"
    "mono_debug_cleanup:\n");

asm(".global mono_debug_close_image\n"
    ".type mono_debug_close_image @function\n"
    "mono_debug_close_image:\n");

asm(".global mono_debug_close_mono_symbol_file\n"
    ".type mono_debug_close_mono_symbol_file @function\n"
    "mono_debug_close_mono_symbol_file:\n");

asm(".global mono_debug_domain_create\n"
    ".type mono_debug_domain_create @function\n"
    "mono_debug_domain_create:\n");

asm(".global mono_debug_domain_unload\n"
    ".type mono_debug_domain_unload @function\n"
    "mono_debug_domain_unload:\n");

asm(".global mono_debug_enabled\n"
    ".type mono_debug_enabled @function\n"
    "mono_debug_enabled:\n");

asm(".global mono_debug_find_method\n"
    ".type mono_debug_find_method @function\n"
    "mono_debug_find_method:\n");

asm(".global mono_debug_free_locals\n"
    ".type mono_debug_free_locals @function\n"
    "mono_debug_free_locals:\n");

asm(".global mono_debug_free_method_jit_info\n"
    ".type mono_debug_free_method_jit_info @function\n"
    "mono_debug_free_method_jit_info:\n");

asm(".global mono_debug_free_source_location\n"
    ".type mono_debug_free_source_location @function\n"
    "mono_debug_free_source_location:\n");

asm(".global mono_debug_il_offset_from_address\n"
    ".type mono_debug_il_offset_from_address @function\n"
    "mono_debug_il_offset_from_address:\n");

asm(".global mono_debug_init\n"
    ".type mono_debug_init @function\n"
    "mono_debug_init:\n");

asm(".global mono_debug_lookup_locals\n"
    ".type mono_debug_lookup_locals @function\n"
    "mono_debug_lookup_locals:\n");

asm(".global mono_debug_lookup_method\n"
    ".type mono_debug_lookup_method @function\n"
    "mono_debug_lookup_method:\n");

asm(".global mono_debug_lookup_method_addresses\n"
    ".type mono_debug_lookup_method_addresses @function\n"
    "mono_debug_lookup_method_addresses:\n");

asm(".global mono_debug_lookup_source_location\n"
    ".type mono_debug_lookup_source_location @function\n"
    "mono_debug_lookup_source_location:\n");

asm(".global mono_debug_open_image_from_memory\n"
    ".type mono_debug_open_image_from_memory @function\n"
    "mono_debug_open_image_from_memory:\n");

asm(".global mono_debug_open_mono_symbols\n"
    ".type mono_debug_open_mono_symbols @function\n"
    "mono_debug_open_mono_symbols:\n");

asm(".global mono_debug_print_stack_frame\n"
    ".type mono_debug_print_stack_frame @function\n"
    "mono_debug_print_stack_frame:\n");

asm(".global mono_debug_print_vars\n"
    ".type mono_debug_print_vars @function\n"
    "mono_debug_print_vars:\n");

asm(".global mono_debug_remove_method\n"
    ".type mono_debug_remove_method @function\n"
    "mono_debug_remove_method:\n");

asm(".global mono_debug_symfile_free_location\n"
    ".type mono_debug_symfile_free_location @function\n"
    "mono_debug_symfile_free_location:\n");

asm(".global mono_debug_symfile_is_loaded\n"
    ".type mono_debug_symfile_is_loaded @function\n"
    "mono_debug_symfile_is_loaded:\n");

asm(".global mono_debug_symfile_lookup_locals\n"
    ".type mono_debug_symfile_lookup_locals @function\n"
    "mono_debug_symfile_lookup_locals:\n");

asm(".global mono_debug_symfile_lookup_location\n"
    ".type mono_debug_symfile_lookup_location @function\n"
    "mono_debug_symfile_lookup_location:\n");

asm(".global mono_debug_symfile_lookup_method\n"
    ".type mono_debug_symfile_lookup_method @function\n"
    "mono_debug_symfile_lookup_method:\n");

asm(".global mono_debugger_agent_parse_options\n"
    ".type mono_debugger_agent_parse_options @function\n"
    "mono_debugger_agent_parse_options:\n");

asm(".global mono_debugger_agent_register_transport\n"
    ".type mono_debugger_agent_register_transport @function\n"
    "mono_debugger_agent_register_transport:\n");

asm(".global mono_debugger_agent_transport_handshake\n"
    ".type mono_debugger_agent_transport_handshake @function\n"
    "mono_debugger_agent_transport_handshake:\n");

asm(".global mono_debugger_insert_breakpoint\n"
    ".type mono_debugger_insert_breakpoint @function\n"
    "mono_debugger_insert_breakpoint:\n");

asm(".global mono_debugger_method_has_breakpoint\n"
    ".type mono_debugger_method_has_breakpoint @function\n"
    "mono_debugger_method_has_breakpoint:\n");

asm(".global mono_debugger_run_finally\n"
    ".type mono_debugger_run_finally @function\n"
    "mono_debugger_run_finally:\n");

asm(".global mono_declsec_flags_from_assembly\n"
    ".type mono_declsec_flags_from_assembly @function\n"
    "mono_declsec_flags_from_assembly:\n");

asm(".global mono_declsec_flags_from_class\n"
    ".type mono_declsec_flags_from_class @function\n"
    "mono_declsec_flags_from_class:\n");

asm(".global mono_declsec_flags_from_method\n"
    ".type mono_declsec_flags_from_method @function\n"
    "mono_declsec_flags_from_method:\n");

asm(".global mono_declsec_get_assembly_action\n"
    ".type mono_declsec_get_assembly_action @function\n"
    "mono_declsec_get_assembly_action:\n");

asm(".global mono_declsec_get_class_action\n"
    ".type mono_declsec_get_class_action @function\n"
    "mono_declsec_get_class_action:\n");

asm(".global mono_declsec_get_demands\n"
    ".type mono_declsec_get_demands @function\n"
    "mono_declsec_get_demands:\n");

asm(".global mono_declsec_get_inheritdemands_class\n"
    ".type mono_declsec_get_inheritdemands_class @function\n"
    "mono_declsec_get_inheritdemands_class:\n");

asm(".global mono_declsec_get_inheritdemands_method\n"
    ".type mono_declsec_get_inheritdemands_method @function\n"
    "mono_declsec_get_inheritdemands_method:\n");

asm(".global mono_declsec_get_linkdemands\n"
    ".type mono_declsec_get_linkdemands @function\n"
    "mono_declsec_get_linkdemands:\n");

asm(".global mono_declsec_get_method_action\n"
    ".type mono_declsec_get_method_action @function\n"
    "mono_declsec_get_method_action:\n");

asm(".global mono_delegate_free_ftnptr\n"
    ".type mono_delegate_free_ftnptr @function\n"
    "mono_delegate_free_ftnptr:\n");

asm(".global mono_delegate_to_ftnptr\n"
    ".type mono_delegate_to_ftnptr @function\n"
    "mono_delegate_to_ftnptr:\n");

asm(".global mono_digest_get_public_token\n"
    ".type mono_digest_get_public_token @function\n"
    "mono_digest_get_public_token:\n");

asm(".global mono_disasm_code\n"
    ".type mono_disasm_code @function\n"
    "mono_disasm_code:\n");

asm(".global mono_disasm_code_one\n"
    ".type mono_disasm_code_one @function\n"
    "mono_disasm_code_one:\n");

asm(".global mono_dl_fallback_register\n"
    ".type mono_dl_fallback_register @function\n"
    "mono_dl_fallback_register:\n");

asm(".global mono_dl_fallback_unregister\n"
    ".type mono_dl_fallback_unregister @function\n"
    "mono_dl_fallback_unregister:\n");

asm(".global mono_dl_open\n"
    ".type mono_dl_open @function\n"
    "mono_dl_open:\n");

asm(".global mono_dllmap_insert\n"
    ".type mono_dllmap_insert @function\n"
    "mono_dllmap_insert:\n");

asm(".global mono_domain_assembly_open\n"
    ".type mono_domain_assembly_open @function\n"
    "mono_domain_assembly_open:\n");

asm(".global mono_domain_create\n"
    ".type mono_domain_create @function\n"
    "mono_domain_create:\n");

asm(".global mono_domain_create_appdomain\n"
    ".type mono_domain_create_appdomain @function\n"
    "mono_domain_create_appdomain:\n");

asm(".global mono_domain_finalize\n"
    ".type mono_domain_finalize @function\n"
    "mono_domain_finalize:\n");

asm(".global mono_domain_foreach\n"
    ".type mono_domain_foreach @function\n"
    "mono_domain_foreach:\n");

asm(".global mono_domain_free\n"
    ".type mono_domain_free @function\n"
    "mono_domain_free:\n");

asm(".global mono_domain_from_appdomain\n"
    ".type mono_domain_from_appdomain @function\n"
    "mono_domain_from_appdomain:\n");

asm(".global mono_domain_get\n"
    ".type mono_domain_get @function\n"
    "mono_domain_get:\n");

asm(".global mono_domain_get_by_id\n"
    ".type mono_domain_get_by_id @function\n"
    "mono_domain_get_by_id:\n");

asm(".global mono_domain_get_friendly_name\n"
    ".type mono_domain_get_friendly_name @function\n"
    "mono_domain_get_friendly_name:\n");

asm(".global mono_domain_get_id\n"
    ".type mono_domain_get_id @function\n"
    "mono_domain_get_id:\n");

asm(".global mono_domain_has_type_resolve\n"
    ".type mono_domain_has_type_resolve @function\n"
    "mono_domain_has_type_resolve:\n");

asm(".global mono_domain_is_unloading\n"
    ".type mono_domain_is_unloading @function\n"
    "mono_domain_is_unloading:\n");

asm(".global mono_domain_owns_vtable_slot\n"
    ".type mono_domain_owns_vtable_slot @function\n"
    "mono_domain_owns_vtable_slot:\n");

asm(".global mono_domain_set\n"
    ".type mono_domain_set @function\n"
    "mono_domain_set:\n");

asm(".global mono_domain_set_config\n"
    ".type mono_domain_set_config @function\n"
    "mono_domain_set_config:\n");

asm(".global mono_domain_set_internal\n"
    ".type mono_domain_set_internal @function\n"
    "mono_domain_set_internal:\n");

asm(".global mono_domain_try_type_resolve\n"
    ".type mono_domain_try_type_resolve @function\n"
    "mono_domain_try_type_resolve:\n");

asm(".global mono_domain_try_unload\n"
    ".type mono_domain_try_unload @function\n"
    "mono_domain_try_unload:\n");

asm(".global mono_domain_unload\n"
    ".type mono_domain_unload @function\n"
    "mono_domain_unload:\n");

asm(".global mono_environment_exitcode_get\n"
    ".type mono_environment_exitcode_get @function\n"
    "mono_environment_exitcode_get:\n");

asm(".global mono_environment_exitcode_set\n"
    ".type mono_environment_exitcode_set @function\n"
    "mono_environment_exitcode_set:\n");

asm(".global mono_error_cleanup\n"
    ".type mono_error_cleanup @function\n"
    "mono_error_cleanup:\n");

asm(".global mono_error_get_error_code\n"
    ".type mono_error_get_error_code @function\n"
    "mono_error_get_error_code:\n");

asm(".global mono_error_get_message\n"
    ".type mono_error_get_message @function\n"
    "mono_error_get_message:\n");

asm(".global mono_error_init\n"
    ".type mono_error_init @function\n"
    "mono_error_init:\n");

asm(".global mono_error_init_flags\n"
    ".type mono_error_init_flags @function\n"
    "mono_error_init_flags:\n");

asm(".global mono_error_ok\n"
    ".type mono_error_ok @function\n"
    "mono_error_ok:\n");

asm(".global mono_escape_uri_string\n"
    ".type mono_escape_uri_string @function\n"
    "mono_escape_uri_string:\n");

asm(".global mono_event_get_add_method\n"
    ".type mono_event_get_add_method @function\n"
    "mono_event_get_add_method:\n");

asm(".global mono_event_get_flags\n"
    ".type mono_event_get_flags @function\n"
    "mono_event_get_flags:\n");

asm(".global mono_event_get_name\n"
    ".type mono_event_get_name @function\n"
    "mono_event_get_name:\n");

asm(".global mono_event_get_object\n"
    ".type mono_event_get_object @function\n"
    "mono_event_get_object:\n");

asm(".global mono_event_get_parent\n"
    ".type mono_event_get_parent @function\n"
    "mono_event_get_parent:\n");

asm(".global mono_event_get_raise_method\n"
    ".type mono_event_get_raise_method @function\n"
    "mono_event_get_raise_method:\n");

asm(".global mono_event_get_remove_method\n"
    ".type mono_event_get_remove_method @function\n"
    "mono_event_get_remove_method:\n");

asm(".global mono_exception_from_name\n"
    ".type mono_exception_from_name @function\n"
    "mono_exception_from_name:\n");

asm(".global mono_exception_from_name_domain\n"
    ".type mono_exception_from_name_domain @function\n"
    "mono_exception_from_name_domain:\n");

asm(".global mono_exception_from_name_msg\n"
    ".type mono_exception_from_name_msg @function\n"
    "mono_exception_from_name_msg:\n");

asm(".global mono_exception_from_name_two_strings\n"
    ".type mono_exception_from_name_two_strings @function\n"
    "mono_exception_from_name_two_strings:\n");

asm(".global mono_exception_from_token\n"
    ".type mono_exception_from_token @function\n"
    "mono_exception_from_token:\n");

asm(".global mono_exception_from_token_two_strings\n"
    ".type mono_exception_from_token_two_strings @function\n"
    "mono_exception_from_token_two_strings:\n");

asm(".global mono_exception_walk_trace\n"
    ".type mono_exception_walk_trace @function\n"
    "mono_exception_walk_trace:\n");

asm(".global mono_field_from_token\n"
    ".type mono_field_from_token @function\n"
    "mono_field_from_token:\n");

asm(".global mono_field_full_name\n"
    ".type mono_field_full_name @function\n"
    "mono_field_full_name:\n");

asm(".global mono_field_get_data\n"
    ".type mono_field_get_data @function\n"
    "mono_field_get_data:\n");

asm(".global mono_field_get_flags\n"
    ".type mono_field_get_flags @function\n"
    "mono_field_get_flags:\n");

asm(".global mono_field_get_name\n"
    ".type mono_field_get_name @function\n"
    "mono_field_get_name:\n");

asm(".global mono_field_get_object\n"
    ".type mono_field_get_object @function\n"
    "mono_field_get_object:\n");

asm(".global mono_field_get_offset\n"
    ".type mono_field_get_offset @function\n"
    "mono_field_get_offset:\n");

asm(".global mono_field_get_parent\n"
    ".type mono_field_get_parent @function\n"
    "mono_field_get_parent:\n");

asm(".global mono_field_get_type\n"
    ".type mono_field_get_type @function\n"
    "mono_field_get_type:\n");

asm(".global mono_field_get_value\n"
    ".type mono_field_get_value @function\n"
    "mono_field_get_value:\n");

asm(".global mono_field_get_value_object\n"
    ".type mono_field_get_value_object @function\n"
    "mono_field_get_value_object:\n");

asm(".global mono_field_set_value\n"
    ".type mono_field_set_value @function\n"
    "mono_field_set_value:\n");

asm(".global mono_field_static_get_value\n"
    ".type mono_field_static_get_value @function\n"
    "mono_field_static_get_value:\n");

asm(".global mono_field_static_set_value\n"
    ".type mono_field_static_set_value @function\n"
    "mono_field_static_set_value:\n");

asm(".global mono_file_map\n"
    ".type mono_file_map @function\n"
    "mono_file_map:\n");

asm(".global mono_file_map_close\n"
    ".type mono_file_map_close @function\n"
    "mono_file_map_close:\n");

asm(".global mono_file_map_fd\n"
    ".type mono_file_map_fd @function\n"
    "mono_file_map_fd:\n");

asm(".global mono_file_map_open\n"
    ".type mono_file_map_open @function\n"
    "mono_file_map_open:\n");

asm(".global mono_file_map_size\n"
    ".type mono_file_map_size @function\n"
    "mono_file_map_size:\n");

asm(".global mono_file_unmap\n"
    ".type mono_file_unmap @function\n"
    "mono_file_unmap:\n");

asm(".global mono_free\n"
    ".type mono_free @function\n"
    "mono_free:\n");

asm(".global mono_free_bstr\n"
    ".type mono_free_bstr @function\n"
    "mono_free_bstr:\n");

asm(".global mono_free_method\n"
    ".type mono_free_method @function\n"
    "mono_free_method:\n");

asm(".global mono_free_verify_list\n"
    ".type mono_free_verify_list @function\n"
    "mono_free_verify_list:\n");

asm(".global mono_g_hash_table_destroy\n"
    ".type mono_g_hash_table_destroy @function\n"
    "mono_g_hash_table_destroy:\n");

asm(".global mono_g_hash_table_find\n"
    ".type mono_g_hash_table_find @function\n"
    "mono_g_hash_table_find:\n");

asm(".global mono_g_hash_table_foreach\n"
    ".type mono_g_hash_table_foreach @function\n"
    "mono_g_hash_table_foreach:\n");

asm(".global mono_g_hash_table_foreach_remove\n"
    ".type mono_g_hash_table_foreach_remove @function\n"
    "mono_g_hash_table_foreach_remove:\n");

asm(".global mono_g_hash_table_insert\n"
    ".type mono_g_hash_table_insert @function\n"
    "mono_g_hash_table_insert:\n");

asm(".global mono_g_hash_table_lookup\n"
    ".type mono_g_hash_table_lookup @function\n"
    "mono_g_hash_table_lookup:\n");

asm(".global mono_g_hash_table_lookup_extended\n"
    ".type mono_g_hash_table_lookup_extended @function\n"
    "mono_g_hash_table_lookup_extended:\n");

asm(".global mono_g_hash_table_new_type\n"
    ".type mono_g_hash_table_new_type @function\n"
    "mono_g_hash_table_new_type:\n");

asm(".global mono_g_hash_table_print_stats\n"
    ".type mono_g_hash_table_print_stats @function\n"
    "mono_g_hash_table_print_stats:\n");

asm(".global mono_g_hash_table_remove\n"
    ".type mono_g_hash_table_remove @function\n"
    "mono_g_hash_table_remove:\n");

asm(".global mono_g_hash_table_replace\n"
    ".type mono_g_hash_table_replace @function\n"
    "mono_g_hash_table_replace:\n");

asm(".global mono_g_hash_table_size\n"
    ".type mono_g_hash_table_size @function\n"
    "mono_g_hash_table_size:\n");

asm(".global mono_gc_collect\n"
    ".type mono_gc_collect @function\n"
    "mono_gc_collect:\n");

asm(".global mono_gc_collection_count\n"
    ".type mono_gc_collection_count @function\n"
    "mono_gc_collection_count:\n");

asm(".global mono_gc_finalize_notify\n"
    ".type mono_gc_finalize_notify @function\n"
    "mono_gc_finalize_notify:\n");

asm(".global mono_gc_get_generation\n"
    ".type mono_gc_get_generation @function\n"
    "mono_gc_get_generation:\n");

asm(".global mono_gc_get_heap_size\n"
    ".type mono_gc_get_heap_size @function\n"
    "mono_gc_get_heap_size:\n");

asm(".global mono_gc_get_used_size\n"
    ".type mono_gc_get_used_size @function\n"
    "mono_gc_get_used_size:\n");

asm(".global mono_gc_invoke_finalizers\n"
    ".type mono_gc_invoke_finalizers @function\n"
    "mono_gc_invoke_finalizers:\n");

asm(".global mono_gc_max_generation\n"
    ".type mono_gc_max_generation @function\n"
    "mono_gc_max_generation:\n");

asm(".global mono_gc_out_of_memory\n"
    ".type mono_gc_out_of_memory @function\n"
    "mono_gc_out_of_memory:\n");

asm(".global mono_gc_reference_queue_add\n"
    ".type mono_gc_reference_queue_add @function\n"
    "mono_gc_reference_queue_add:\n");

asm(".global mono_gc_reference_queue_free\n"
    ".type mono_gc_reference_queue_free @function\n"
    "mono_gc_reference_queue_free:\n");

asm(".global mono_gc_reference_queue_new\n"
    ".type mono_gc_reference_queue_new @function\n"
    "mono_gc_reference_queue_new:\n");

asm(".global mono_gc_register_bridge_callbacks\n"
    ".type mono_gc_register_bridge_callbacks @function\n"
    "mono_gc_register_bridge_callbacks:\n");

asm(".global mono_gc_register_finalizer_callbacks\n"
    ".type mono_gc_register_finalizer_callbacks @function\n"
    "mono_gc_register_finalizer_callbacks:\n");

asm(".global mono_gc_register_root\n"
    ".type mono_gc_register_root @function\n"
    "mono_gc_register_root:\n");

asm(".global mono_gc_set_heap_size_limit\n"
    ".type mono_gc_set_heap_size_limit @function\n"
    "mono_gc_set_heap_size_limit:\n");

asm(".global mono_gc_toggleref_add\n"
    ".type mono_gc_toggleref_add @function\n"
    "mono_gc_toggleref_add:\n");

asm(".global mono_gc_toggleref_register_callback\n"
    ".type mono_gc_toggleref_register_callback @function\n"
    "mono_gc_toggleref_register_callback:\n");

asm(".global mono_gc_wait_for_bridge_processing\n"
    ".type mono_gc_wait_for_bridge_processing @function\n"
    "mono_gc_wait_for_bridge_processing:\n");

asm(".global mono_gc_walk_heap\n"
    ".type mono_gc_walk_heap @function\n"
    "mono_gc_walk_heap:\n");

asm(".global mono_gc_wbarrier_arrayref_copy\n"
    ".type mono_gc_wbarrier_arrayref_copy @function\n"
    "mono_gc_wbarrier_arrayref_copy:\n");

asm(".global mono_gc_wbarrier_generic_nostore\n"
    ".type mono_gc_wbarrier_generic_nostore @function\n"
    "mono_gc_wbarrier_generic_nostore:\n");

asm(".global mono_gc_wbarrier_generic_store\n"
    ".type mono_gc_wbarrier_generic_store @function\n"
    "mono_gc_wbarrier_generic_store:\n");

asm(".global mono_gc_wbarrier_generic_store_atomic\n"
    ".type mono_gc_wbarrier_generic_store_atomic @function\n"
    "mono_gc_wbarrier_generic_store_atomic:\n");

asm(".global mono_gc_wbarrier_object_copy\n"
    ".type mono_gc_wbarrier_object_copy @function\n"
    "mono_gc_wbarrier_object_copy:\n");

asm(".global mono_gc_wbarrier_set_arrayref\n"
    ".type mono_gc_wbarrier_set_arrayref @function\n"
    "mono_gc_wbarrier_set_arrayref:\n");

asm(".global mono_gc_wbarrier_set_field\n"
    ".type mono_gc_wbarrier_set_field @function\n"
    "mono_gc_wbarrier_set_field:\n");

asm(".global mono_gc_wbarrier_value_copy\n"
    ".type mono_gc_wbarrier_value_copy @function\n"
    "mono_gc_wbarrier_value_copy:\n");

asm(".global mono_gchandle_free\n"
    ".type mono_gchandle_free @function\n"
    "mono_gchandle_free:\n");

asm(".global mono_gchandle_get_target\n"
    ".type mono_gchandle_get_target @function\n"
    "mono_gchandle_get_target:\n");

asm(".global mono_gchandle_new\n"
    ".type mono_gchandle_new @function\n"
    "mono_gchandle_new:\n");

asm(".global mono_gchandle_new_weakref\n"
    ".type mono_gchandle_new_weakref @function\n"
    "mono_gchandle_new_weakref:\n");

asm(".global mono_get_array_class\n"
    ".type mono_get_array_class @function\n"
    "mono_get_array_class:\n");

asm(".global mono_get_boolean_class\n"
    ".type mono_get_boolean_class @function\n"
    "mono_get_boolean_class:\n");

asm(".global mono_get_byte_class\n"
    ".type mono_get_byte_class @function\n"
    "mono_get_byte_class:\n");

asm(".global mono_get_char_class\n"
    ".type mono_get_char_class @function\n"
    "mono_get_char_class:\n");

asm(".global mono_get_config_dir\n"
    ".type mono_get_config_dir @function\n"
    "mono_get_config_dir:\n");

asm(".global mono_get_corlib\n"
    ".type mono_get_corlib @function\n"
    "mono_get_corlib:\n");

asm(".global mono_get_dbnull_object\n"
    ".type mono_get_dbnull_object @function\n"
    "mono_get_dbnull_object:\n");

asm(".global mono_get_delegate_begin_invoke\n"
    ".type mono_get_delegate_begin_invoke @function\n"
    "mono_get_delegate_begin_invoke:\n");

asm(".global mono_get_delegate_end_invoke\n"
    ".type mono_get_delegate_end_invoke @function\n"
    "mono_get_delegate_end_invoke:\n");

asm(".global mono_get_delegate_invoke\n"
    ".type mono_get_delegate_invoke @function\n"
    "mono_get_delegate_invoke:\n");

asm(".global mono_get_double_class\n"
    ".type mono_get_double_class @function\n"
    "mono_get_double_class:\n");

asm(".global mono_get_enum_class\n"
    ".type mono_get_enum_class @function\n"
    "mono_get_enum_class:\n");

asm(".global mono_get_exception_appdomain_unloaded\n"
    ".type mono_get_exception_appdomain_unloaded @function\n"
    "mono_get_exception_appdomain_unloaded:\n");

asm(".global mono_get_exception_argument\n"
    ".type mono_get_exception_argument @function\n"
    "mono_get_exception_argument:\n");

asm(".global mono_get_exception_argument_null\n"
    ".type mono_get_exception_argument_null @function\n"
    "mono_get_exception_argument_null:\n");

asm(".global mono_get_exception_argument_out_of_range\n"
    ".type mono_get_exception_argument_out_of_range @function\n"
    "mono_get_exception_argument_out_of_range:\n");

asm(".global mono_get_exception_arithmetic\n"
    ".type mono_get_exception_arithmetic @function\n"
    "mono_get_exception_arithmetic:\n");

asm(".global mono_get_exception_array_type_mismatch\n"
    ".type mono_get_exception_array_type_mismatch @function\n"
    "mono_get_exception_array_type_mismatch:\n");

asm(".global mono_get_exception_bad_image_format\n"
    ".type mono_get_exception_bad_image_format @function\n"
    "mono_get_exception_bad_image_format:\n");

asm(".global mono_get_exception_bad_image_format2\n"
    ".type mono_get_exception_bad_image_format2 @function\n"
    "mono_get_exception_bad_image_format2:\n");

asm(".global mono_get_exception_cannot_unload_appdomain\n"
    ".type mono_get_exception_cannot_unload_appdomain @function\n"
    "mono_get_exception_cannot_unload_appdomain:\n");

asm(".global mono_get_exception_class\n"
    ".type mono_get_exception_class @function\n"
    "mono_get_exception_class:\n");

asm(".global mono_get_exception_divide_by_zero\n"
    ".type mono_get_exception_divide_by_zero @function\n"
    "mono_get_exception_divide_by_zero:\n");

asm(".global mono_get_exception_execution_engine\n"
    ".type mono_get_exception_execution_engine @function\n"
    "mono_get_exception_execution_engine:\n");

asm(".global mono_get_exception_field_access\n"
    ".type mono_get_exception_field_access @function\n"
    "mono_get_exception_field_access:\n");

asm(".global mono_get_exception_file_not_found\n"
    ".type mono_get_exception_file_not_found @function\n"
    "mono_get_exception_file_not_found:\n");

asm(".global mono_get_exception_file_not_found2\n"
    ".type mono_get_exception_file_not_found2 @function\n"
    "mono_get_exception_file_not_found2:\n");

asm(".global mono_get_exception_index_out_of_range\n"
    ".type mono_get_exception_index_out_of_range @function\n"
    "mono_get_exception_index_out_of_range:\n");

asm(".global mono_get_exception_invalid_cast\n"
    ".type mono_get_exception_invalid_cast @function\n"
    "mono_get_exception_invalid_cast:\n");

asm(".global mono_get_exception_invalid_operation\n"
    ".type mono_get_exception_invalid_operation @function\n"
    "mono_get_exception_invalid_operation:\n");

asm(".global mono_get_exception_io\n"
    ".type mono_get_exception_io @function\n"
    "mono_get_exception_io:\n");

asm(".global mono_get_exception_method_access\n"
    ".type mono_get_exception_method_access @function\n"
    "mono_get_exception_method_access:\n");

asm(".global mono_get_exception_missing_field\n"
    ".type mono_get_exception_missing_field @function\n"
    "mono_get_exception_missing_field:\n");

asm(".global mono_get_exception_missing_method\n"
    ".type mono_get_exception_missing_method @function\n"
    "mono_get_exception_missing_method:\n");

asm(".global mono_get_exception_not_implemented\n"
    ".type mono_get_exception_not_implemented @function\n"
    "mono_get_exception_not_implemented:\n");

asm(".global mono_get_exception_not_supported\n"
    ".type mono_get_exception_not_supported @function\n"
    "mono_get_exception_not_supported:\n");

asm(".global mono_get_exception_null_reference\n"
    ".type mono_get_exception_null_reference @function\n"
    "mono_get_exception_null_reference:\n");

asm(".global mono_get_exception_out_of_memory\n"
    ".type mono_get_exception_out_of_memory @function\n"
    "mono_get_exception_out_of_memory:\n");

asm(".global mono_get_exception_overflow\n"
    ".type mono_get_exception_overflow @function\n"
    "mono_get_exception_overflow:\n");

asm(".global mono_get_exception_reflection_type_load\n"
    ".type mono_get_exception_reflection_type_load @function\n"
    "mono_get_exception_reflection_type_load:\n");

asm(".global mono_get_exception_runtime_wrapped\n"
    ".type mono_get_exception_runtime_wrapped @function\n"
    "mono_get_exception_runtime_wrapped:\n");

asm(".global mono_get_exception_security\n"
    ".type mono_get_exception_security @function\n"
    "mono_get_exception_security:\n");

asm(".global mono_get_exception_serialization\n"
    ".type mono_get_exception_serialization @function\n"
    "mono_get_exception_serialization:\n");

asm(".global mono_get_exception_stack_overflow\n"
    ".type mono_get_exception_stack_overflow @function\n"
    "mono_get_exception_stack_overflow:\n");

asm(".global mono_get_exception_synchronization_lock\n"
    ".type mono_get_exception_synchronization_lock @function\n"
    "mono_get_exception_synchronization_lock:\n");

asm(".global mono_get_exception_thread_abort\n"
    ".type mono_get_exception_thread_abort @function\n"
    "mono_get_exception_thread_abort:\n");

asm(".global mono_get_exception_thread_interrupted\n"
    ".type mono_get_exception_thread_interrupted @function\n"
    "mono_get_exception_thread_interrupted:\n");

asm(".global mono_get_exception_thread_state\n"
    ".type mono_get_exception_thread_state @function\n"
    "mono_get_exception_thread_state:\n");

asm(".global mono_get_exception_type_initialization\n"
    ".type mono_get_exception_type_initialization @function\n"
    "mono_get_exception_type_initialization:\n");

asm(".global mono_get_exception_type_load\n"
    ".type mono_get_exception_type_load @function\n"
    "mono_get_exception_type_load:\n");

asm(".global mono_get_inflated_method\n"
    ".type mono_get_inflated_method @function\n"
    "mono_get_inflated_method:\n");

asm(".global mono_get_int16_class\n"
    ".type mono_get_int16_class @function\n"
    "mono_get_int16_class:\n");

asm(".global mono_get_int32_class\n"
    ".type mono_get_int32_class @function\n"
    "mono_get_int32_class:\n");

asm(".global mono_get_int64_class\n"
    ".type mono_get_int64_class @function\n"
    "mono_get_int64_class:\n");

asm(".global mono_get_intptr_class\n"
    ".type mono_get_intptr_class @function\n"
    "mono_get_intptr_class:\n");

asm(".global mono_get_machine_config\n"
    ".type mono_get_machine_config @function\n"
    "mono_get_machine_config:\n");

asm(".global mono_get_method\n"
    ".type mono_get_method @function\n"
    "mono_get_method:\n");

asm(".global mono_get_method_constrained\n"
    ".type mono_get_method_constrained @function\n"
    "mono_get_method_constrained:\n");

asm(".global mono_get_method_full\n"
    ".type mono_get_method_full @function\n"
    "mono_get_method_full:\n");

asm(".global mono_get_object_class\n"
    ".type mono_get_object_class @function\n"
    "mono_get_object_class:\n");

asm(".global mono_get_root_domain\n"
    ".type mono_get_root_domain @function\n"
    "mono_get_root_domain:\n");

asm(".global mono_get_runtime_build_info\n"
    ".type mono_get_runtime_build_info @function\n"
    "mono_get_runtime_build_info:\n");

asm(".global mono_get_sbyte_class\n"
    ".type mono_get_sbyte_class @function\n"
    "mono_get_sbyte_class:\n");

asm(".global mono_get_single_class\n"
    ".type mono_get_single_class @function\n"
    "mono_get_single_class:\n");

asm(".global mono_get_string_class\n"
    ".type mono_get_string_class @function\n"
    "mono_get_string_class:\n");

asm(".global mono_get_thread_class\n"
    ".type mono_get_thread_class @function\n"
    "mono_get_thread_class:\n");

asm(".global mono_get_uint16_class\n"
    ".type mono_get_uint16_class @function\n"
    "mono_get_uint16_class:\n");

asm(".global mono_get_uint32_class\n"
    ".type mono_get_uint32_class @function\n"
    "mono_get_uint32_class:\n");

asm(".global mono_get_uint64_class\n"
    ".type mono_get_uint64_class @function\n"
    "mono_get_uint64_class:\n");

asm(".global mono_get_uintptr_class\n"
    ".type mono_get_uintptr_class @function\n"
    "mono_get_uintptr_class:\n");

asm(".global mono_get_void_class\n"
    ".type mono_get_void_class @function\n"
    "mono_get_void_class:\n");

asm(".global mono_guid_to_string\n"
    ".type mono_guid_to_string @function\n"
    "mono_guid_to_string:\n");

asm(".global mono_guid_to_string_minimal\n"
    ".type mono_guid_to_string_minimal @function\n"
    "mono_guid_to_string_minimal:\n");

asm(".global mono_hazard_pointer_get\n"
    ".type mono_hazard_pointer_get @function\n"
    "mono_hazard_pointer_get:\n");

asm(".global mono_image_add_to_name_cache\n"
    ".type mono_image_add_to_name_cache @function\n"
    "mono_image_add_to_name_cache:\n");

asm(".global mono_image_addref\n"
    ".type mono_image_addref @function\n"
    "mono_image_addref:\n");

asm(".global mono_image_close\n"
    ".type mono_image_close @function\n"
    "mono_image_close:\n");

asm(".global mono_image_ensure_section\n"
    ".type mono_image_ensure_section @function\n"
    "mono_image_ensure_section:\n");

asm(".global mono_image_ensure_section_idx\n"
    ".type mono_image_ensure_section_idx @function\n"
    "mono_image_ensure_section_idx:\n");

asm(".global mono_image_fixup_vtable\n"
    ".type mono_image_fixup_vtable @function\n"
    "mono_image_fixup_vtable:\n");

asm(".global mono_image_get_assembly\n"
    ".type mono_image_get_assembly @function\n"
    "mono_image_get_assembly:\n");

asm(".global mono_image_get_entry_point\n"
    ".type mono_image_get_entry_point @function\n"
    "mono_image_get_entry_point:\n");

asm(".global mono_image_get_filename\n"
    ".type mono_image_get_filename @function\n"
    "mono_image_get_filename:\n");

asm(".global mono_image_get_guid\n"
    ".type mono_image_get_guid @function\n"
    "mono_image_get_guid:\n");

asm(".global mono_image_get_name\n"
    ".type mono_image_get_name @function\n"
    "mono_image_get_name:\n");

asm(".global mono_image_get_public_key\n"
    ".type mono_image_get_public_key @function\n"
    "mono_image_get_public_key:\n");

asm(".global mono_image_get_resource\n"
    ".type mono_image_get_resource @function\n"
    "mono_image_get_resource:\n");

asm(".global mono_image_get_strong_name\n"
    ".type mono_image_get_strong_name @function\n"
    "mono_image_get_strong_name:\n");

asm(".global mono_image_get_table_info\n"
    ".type mono_image_get_table_info @function\n"
    "mono_image_get_table_info:\n");

asm(".global mono_image_get_table_rows\n"
    ".type mono_image_get_table_rows @function\n"
    "mono_image_get_table_rows:\n");

asm(".global mono_image_has_authenticode_entry\n"
    ".type mono_image_has_authenticode_entry @function\n"
    "mono_image_has_authenticode_entry:\n");

asm(".global mono_image_init\n"
    ".type mono_image_init @function\n"
    "mono_image_init:\n");

asm(".global mono_image_init_name_cache\n"
    ".type mono_image_init_name_cache @function\n"
    "mono_image_init_name_cache:\n");

asm(".global mono_image_is_dynamic\n"
    ".type mono_image_is_dynamic @function\n"
    "mono_image_is_dynamic:\n");

asm(".global mono_image_load_file_for_image\n"
    ".type mono_image_load_file_for_image @function\n"
    "mono_image_load_file_for_image:\n");

asm(".global mono_image_load_module\n"
    ".type mono_image_load_module @function\n"
    "mono_image_load_module:\n");

asm(".global mono_image_loaded\n"
    ".type mono_image_loaded @function\n"
    "mono_image_loaded:\n");

asm(".global mono_image_loaded_by_guid\n"
    ".type mono_image_loaded_by_guid @function\n"
    "mono_image_loaded_by_guid:\n");

asm(".global mono_image_loaded_by_guid_full\n"
    ".type mono_image_loaded_by_guid_full @function\n"
    "mono_image_loaded_by_guid_full:\n");

asm(".global mono_image_loaded_full\n"
    ".type mono_image_loaded_full @function\n"
    "mono_image_loaded_full:\n");

asm(".global mono_image_lookup_resource\n"
    ".type mono_image_lookup_resource @function\n"
    "mono_image_lookup_resource:\n");

asm(".global mono_image_open\n"
    ".type mono_image_open @function\n"
    "mono_image_open:\n");

asm(".global mono_image_open_from_data\n"
    ".type mono_image_open_from_data @function\n"
    "mono_image_open_from_data:\n");

asm(".global mono_image_open_from_data_full\n"
    ".type mono_image_open_from_data_full @function\n"
    "mono_image_open_from_data_full:\n");

asm(".global mono_image_open_from_data_with_name\n"
    ".type mono_image_open_from_data_with_name @function\n"
    "mono_image_open_from_data_with_name:\n");

asm(".global mono_image_open_full\n"
    ".type mono_image_open_full @function\n"
    "mono_image_open_full:\n");

asm(".global mono_image_rva_map\n"
    ".type mono_image_rva_map @function\n"
    "mono_image_rva_map:\n");

asm(".global mono_image_strerror\n"
    ".type mono_image_strerror @function\n"
    "mono_image_strerror:\n");

asm(".global mono_image_strong_name_position\n"
    ".type mono_image_strong_name_position @function\n"
    "mono_image_strong_name_position:\n");

asm(".global mono_images_cleanup\n"
    ".type mono_images_cleanup @function\n"
    "mono_images_cleanup:\n");

asm(".global mono_images_init\n"
    ".type mono_images_init @function\n"
    "mono_images_init:\n");

asm(".global mono_init\n"
    ".type mono_init @function\n"
    "mono_init:\n");

asm(".global mono_init_from_assembly\n"
    ".type mono_init_from_assembly @function\n"
    "mono_init_from_assembly:\n");

asm(".global mono_init_version\n"
    ".type mono_init_version @function\n"
    "mono_init_version:\n");

asm(".global mono_install_assembly_load_hook\n"
    ".type mono_install_assembly_load_hook @function\n"
    "mono_install_assembly_load_hook:\n");

asm(".global mono_install_assembly_postload_refonly_search_hook\n"
    ".type mono_install_assembly_postload_refonly_search_hook @function\n"
    "mono_install_assembly_postload_refonly_search_hook:\n");

asm(".global mono_install_assembly_postload_search_hook\n"
    ".type mono_install_assembly_postload_search_hook @function\n"
    "mono_install_assembly_postload_search_hook:\n");

asm(".global mono_install_assembly_preload_hook\n"
    ".type mono_install_assembly_preload_hook @function\n"
    "mono_install_assembly_preload_hook:\n");

asm(".global mono_install_assembly_refonly_preload_hook\n"
    ".type mono_install_assembly_refonly_preload_hook @function\n"
    "mono_install_assembly_refonly_preload_hook:\n");

asm(".global mono_install_assembly_refonly_search_hook\n"
    ".type mono_install_assembly_refonly_search_hook @function\n"
    "mono_install_assembly_refonly_search_hook:\n");

asm(".global mono_install_assembly_search_hook\n"
    ".type mono_install_assembly_search_hook @function\n"
    "mono_install_assembly_search_hook:\n");

asm(".global mono_install_ftnptr_eh_callback\n"
    ".type mono_install_ftnptr_eh_callback @function\n"
    "mono_install_ftnptr_eh_callback:\n");

asm(".global mono_install_load_aot_data_hook\n"
    ".type mono_install_load_aot_data_hook @function\n"
    "mono_install_load_aot_data_hook:\n");

asm(".global mono_install_runtime_cleanup\n"
    ".type mono_install_runtime_cleanup @function\n"
    "mono_install_runtime_cleanup:\n");

asm(".global mono_install_unhandled_exception_hook\n"
    ".type mono_install_unhandled_exception_hook @function\n"
    "mono_install_unhandled_exception_hook:\n");

asm(".global mono_is_debugger_attached\n"
    ".type mono_is_debugger_attached @function\n"
    "mono_is_debugger_attached:\n");

asm(".global mono_jit_cleanup\n"
    ".type mono_jit_cleanup @function\n"
    "mono_jit_cleanup:\n");

asm(".global mono_jit_exec\n"
    ".type mono_jit_exec @function\n"
    "mono_jit_exec:\n");

asm(".global mono_jit_info_get_code_size\n"
    ".type mono_jit_info_get_code_size @function\n"
    "mono_jit_info_get_code_size:\n");

asm(".global mono_jit_info_get_code_start\n"
    ".type mono_jit_info_get_code_start @function\n"
    "mono_jit_info_get_code_start:\n");

asm(".global mono_jit_info_get_method\n"
    ".type mono_jit_info_get_method @function\n"
    "mono_jit_info_get_method:\n");

asm(".global mono_jit_info_table_find\n"
    ".type mono_jit_info_table_find @function\n"
    "mono_jit_info_table_find:\n");

asm(".global mono_jit_init\n"
    ".type mono_jit_init @function\n"
    "mono_jit_init:\n");

asm(".global mono_jit_init_version\n"
    ".type mono_jit_init_version @function\n"
    "mono_jit_init_version:\n");

asm(".global mono_jit_parse_options\n"
    ".type mono_jit_parse_options @function\n"
    "mono_jit_parse_options:\n");

asm(".global mono_jit_set_aot_mode\n"
    ".type mono_jit_set_aot_mode @function\n"
    "mono_jit_set_aot_mode:\n");

asm(".global mono_jit_set_aot_only\n"
    ".type mono_jit_set_aot_only @function\n"
    "mono_jit_set_aot_only:\n");

asm(".global mono_jit_set_domain\n"
    ".type mono_jit_set_domain @function\n"
    "mono_jit_set_domain:\n");

asm(".global mono_jit_set_trace_options\n"
    ".type mono_jit_set_trace_options @function\n"
    "mono_jit_set_trace_options:\n");

asm(".global mono_jit_thread_attach\n"
    ".type mono_jit_thread_attach @function\n"
    "mono_jit_thread_attach:\n");

asm(".global mono_ldstr\n"
    ".type mono_ldstr @function\n"
    "mono_ldstr:\n");

asm(".global mono_ldtoken\n"
    ".type mono_ldtoken @function\n"
    "mono_ldtoken:\n");

asm(".global mono_lls_get_hazardous_pointer_with_mask\n"
    ".type mono_lls_get_hazardous_pointer_with_mask @function\n"
    "mono_lls_get_hazardous_pointer_with_mask:\n");

asm(".global mono_lls_init\n"
    ".type mono_lls_init @function\n"
    "mono_lls_init:\n");

asm(".global mono_lls_insert\n"
    ".type mono_lls_insert @function\n"
    "mono_lls_insert:\n");

asm(".global mono_lls_remove\n"
    ".type mono_lls_remove @function\n"
    "mono_lls_remove:\n");

asm(".global mono_loader_register_module\n"
    ".type mono_loader_register_module @function\n"
    "mono_loader_register_module:\n");

asm(".global mono_lock_free_alloc\n"
    ".type mono_lock_free_alloc @function\n"
    "mono_lock_free_alloc:\n");

asm(".global mono_lock_free_allocator_check_consistency\n"
    ".type mono_lock_free_allocator_check_consistency @function\n"
    "mono_lock_free_allocator_check_consistency:\n");

asm(".global mono_lock_free_allocator_init_allocator\n"
    ".type mono_lock_free_allocator_init_allocator @function\n"
    "mono_lock_free_allocator_init_allocator:\n");

asm(".global mono_lock_free_allocator_init_size_class\n"
    ".type mono_lock_free_allocator_init_size_class @function\n"
    "mono_lock_free_allocator_init_size_class:\n");

asm(".global mono_lock_free_free\n"
    ".type mono_lock_free_free @function\n"
    "mono_lock_free_free:\n");

asm(".global mono_lock_free_queue_dequeue\n"
    ".type mono_lock_free_queue_dequeue @function\n"
    "mono_lock_free_queue_dequeue:\n");

asm(".global mono_lock_free_queue_enqueue\n"
    ".type mono_lock_free_queue_enqueue @function\n"
    "mono_lock_free_queue_enqueue:\n");

asm(".global mono_lock_free_queue_init\n"
    ".type mono_lock_free_queue_init @function\n"
    "mono_lock_free_queue_init:\n");

asm(".global mono_lock_free_queue_node_init\n"
    ".type mono_lock_free_queue_node_init @function\n"
    "mono_lock_free_queue_node_init:\n");

asm(".global mono_lock_free_queue_node_unpoison\n"
    ".type mono_lock_free_queue_node_unpoison @function\n"
    "mono_lock_free_queue_node_unpoison:\n");

asm(".global mono_locks_dump\n"
    ".type mono_locks_dump @function\n"
    "mono_locks_dump:\n");

asm(".global mono_log_close_logfile\n"
    ".type mono_log_close_logfile @function\n"
    "mono_log_close_logfile:\n");

asm(".global mono_log_close_syslog\n"
    ".type mono_log_close_syslog @function\n"
    "mono_log_close_syslog:\n");

asm(".global mono_log_open_logfile\n"
    ".type mono_log_open_logfile @function\n"
    "mono_log_open_logfile:\n");

asm(".global mono_log_open_syslog\n"
    ".type mono_log_open_syslog @function\n"
    "mono_log_open_syslog:\n");

asm(".global mono_log_write_logfile\n"
    ".type mono_log_write_logfile @function\n"
    "mono_log_write_logfile:\n");

asm(".global mono_log_write_syslog\n"
    ".type mono_log_write_syslog @function\n"
    "mono_log_write_syslog:\n");

asm(".global mono_lookup_icall_symbol\n"
    ".type mono_lookup_icall_symbol @function\n"
    "mono_lookup_icall_symbol:\n");

asm(".global mono_lookup_internal_call\n"
    ".type mono_lookup_internal_call @function\n"
    "mono_lookup_internal_call:\n");

asm(".global mono_lookup_pinvoke_call\n"
    ".type mono_lookup_pinvoke_call @function\n"
    "mono_lookup_pinvoke_call:\n");

asm(".global mono_main\n"
    ".type mono_main @function\n"
    "mono_main:\n");

asm(".global mono_marshal_string_to_utf16\n"
    ".type mono_marshal_string_to_utf16 @function\n"
    "mono_marshal_string_to_utf16:\n");

asm(".global mono_md5_final\n"
    ".type mono_md5_final @function\n"
    "mono_md5_final:\n");

asm(".global mono_md5_get_digest\n"
    ".type mono_md5_get_digest @function\n"
    "mono_md5_get_digest:\n");

asm(".global mono_md5_get_digest_from_file\n"
    ".type mono_md5_get_digest_from_file @function\n"
    "mono_md5_get_digest_from_file:\n");

asm(".global mono_md5_init\n"
    ".type mono_md5_init @function\n"
    "mono_md5_init:\n");

asm(".global mono_md5_update\n"
    ".type mono_md5_update @function\n"
    "mono_md5_update:\n");

asm(".global mono_mempool_alloc\n"
    ".type mono_mempool_alloc @function\n"
    "mono_mempool_alloc:\n");

asm(".global mono_mempool_alloc0\n"
    ".type mono_mempool_alloc0 @function\n"
    "mono_mempool_alloc0:\n");

asm(".global mono_mempool_contains_addr\n"
    ".type mono_mempool_contains_addr @function\n"
    "mono_mempool_contains_addr:\n");

asm(".global mono_mempool_destroy\n"
    ".type mono_mempool_destroy @function\n"
    "mono_mempool_destroy:\n");

asm(".global mono_mempool_get_allocated\n"
    ".type mono_mempool_get_allocated @function\n"
    "mono_mempool_get_allocated:\n");

asm(".global mono_mempool_invalidate\n"
    ".type mono_mempool_invalidate @function\n"
    "mono_mempool_invalidate:\n");

asm(".global mono_mempool_new\n"
    ".type mono_mempool_new @function\n"
    "mono_mempool_new:\n");

asm(".global mono_mempool_new_size\n"
    ".type mono_mempool_new_size @function\n"
    "mono_mempool_new_size:\n");

asm(".global mono_mempool_stats\n"
    ".type mono_mempool_stats @function\n"
    "mono_mempool_stats:\n");

asm(".global mono_mempool_strdup\n"
    ".type mono_mempool_strdup @function\n"
    "mono_mempool_strdup:\n");

asm(".global mono_metadata_blob_heap\n"
    ".type mono_metadata_blob_heap @function\n"
    "mono_metadata_blob_heap:\n");

asm(".global mono_metadata_cleanup\n"
    ".type mono_metadata_cleanup @function\n"
    "mono_metadata_cleanup:\n");

asm(".global mono_metadata_compute_size\n"
    ".type mono_metadata_compute_size @function\n"
    "mono_metadata_compute_size:\n");

asm(".global mono_metadata_custom_attrs_from_index\n"
    ".type mono_metadata_custom_attrs_from_index @function\n"
    "mono_metadata_custom_attrs_from_index:\n");

asm(".global mono_metadata_declsec_from_index\n"
    ".type mono_metadata_declsec_from_index @function\n"
    "mono_metadata_declsec_from_index:\n");

asm(".global mono_metadata_decode_blob_size\n"
    ".type mono_metadata_decode_blob_size @function\n"
    "mono_metadata_decode_blob_size:\n");

asm(".global mono_metadata_decode_row\n"
    ".type mono_metadata_decode_row @function\n"
    "mono_metadata_decode_row:\n");

asm(".global mono_metadata_decode_row_col\n"
    ".type mono_metadata_decode_row_col @function\n"
    "mono_metadata_decode_row_col:\n");

asm(".global mono_metadata_decode_signed_value\n"
    ".type mono_metadata_decode_signed_value @function\n"
    "mono_metadata_decode_signed_value:\n");

asm(".global mono_metadata_decode_table_row\n"
    ".type mono_metadata_decode_table_row @function\n"
    "mono_metadata_decode_table_row:\n");

asm(".global mono_metadata_decode_table_row_col\n"
    ".type mono_metadata_decode_table_row_col @function\n"
    "mono_metadata_decode_table_row_col:\n");

asm(".global mono_metadata_decode_value\n"
    ".type mono_metadata_decode_value @function\n"
    "mono_metadata_decode_value:\n");

asm(".global mono_metadata_encode_value\n"
    ".type mono_metadata_encode_value @function\n"
    "mono_metadata_encode_value:\n");

asm(".global mono_metadata_events_from_typedef\n"
    ".type mono_metadata_events_from_typedef @function\n"
    "mono_metadata_events_from_typedef:\n");

asm(".global mono_metadata_field_info\n"
    ".type mono_metadata_field_info @function\n"
    "mono_metadata_field_info:\n");

asm(".global mono_metadata_field_info_with_mempool\n"
    ".type mono_metadata_field_info_with_mempool @function\n"
    "mono_metadata_field_info_with_mempool:\n");

asm(".global mono_metadata_free_array\n"
    ".type mono_metadata_free_array @function\n"
    "mono_metadata_free_array:\n");

asm(".global mono_metadata_free_inflated_signature\n"
    ".type mono_metadata_free_inflated_signature @function\n"
    "mono_metadata_free_inflated_signature:\n");

asm(".global mono_metadata_free_marshal_spec\n"
    ".type mono_metadata_free_marshal_spec @function\n"
    "mono_metadata_free_marshal_spec:\n");

asm(".global mono_metadata_free_method_signature\n"
    ".type mono_metadata_free_method_signature @function\n"
    "mono_metadata_free_method_signature:\n");

asm(".global mono_metadata_free_mh\n"
    ".type mono_metadata_free_mh @function\n"
    "mono_metadata_free_mh:\n");

asm(".global mono_metadata_free_type\n"
    ".type mono_metadata_free_type @function\n"
    "mono_metadata_free_type:\n");

asm(".global mono_metadata_generic_class_is_valuetype\n"
    ".type mono_metadata_generic_class_is_valuetype @function\n"
    "mono_metadata_generic_class_is_valuetype:\n");

asm(".global mono_metadata_get_constant_index\n"
    ".type mono_metadata_get_constant_index @function\n"
    "mono_metadata_get_constant_index:\n");

asm(".global mono_metadata_get_generic_param_row\n"
    ".type mono_metadata_get_generic_param_row @function\n"
    "mono_metadata_get_generic_param_row:\n");

asm(".global mono_metadata_get_inflated_signature\n"
    ".type mono_metadata_get_inflated_signature @function\n"
    "mono_metadata_get_inflated_signature:\n");

asm(".global mono_metadata_get_marshal_info\n"
    ".type mono_metadata_get_marshal_info @function\n"
    "mono_metadata_get_marshal_info:\n");

asm(".global mono_metadata_guid_heap\n"
    ".type mono_metadata_guid_heap @function\n"
    "mono_metadata_guid_heap:\n");

asm(".global mono_metadata_implmap_from_method\n"
    ".type mono_metadata_implmap_from_method @function\n"
    "mono_metadata_implmap_from_method:\n");

asm(".global mono_metadata_init\n"
    ".type mono_metadata_init @function\n"
    "mono_metadata_init:\n");

asm(".global mono_metadata_interfaces_from_typedef\n"
    ".type mono_metadata_interfaces_from_typedef @function\n"
    "mono_metadata_interfaces_from_typedef:\n");

asm(".global mono_metadata_load_generic_param_constraints_checked\n"
    ".type mono_metadata_load_generic_param_constraints_checked @function\n"
    "mono_metadata_load_generic_param_constraints_checked:\n");

asm(".global mono_metadata_load_generic_params\n"
    ".type mono_metadata_load_generic_params @function\n"
    "mono_metadata_load_generic_params:\n");

asm(".global mono_metadata_locate\n"
    ".type mono_metadata_locate @function\n"
    "mono_metadata_locate:\n");

asm(".global mono_metadata_locate_token\n"
    ".type mono_metadata_locate_token @function\n"
    "mono_metadata_locate_token:\n");

asm(".global mono_metadata_methods_from_event\n"
    ".type mono_metadata_methods_from_event @function\n"
    "mono_metadata_methods_from_event:\n");

asm(".global mono_metadata_methods_from_property\n"
    ".type mono_metadata_methods_from_property @function\n"
    "mono_metadata_methods_from_property:\n");

asm(".global mono_metadata_nested_in_typedef\n"
    ".type mono_metadata_nested_in_typedef @function\n"
    "mono_metadata_nested_in_typedef:\n");

asm(".global mono_metadata_nesting_typedef\n"
    ".type mono_metadata_nesting_typedef @function\n"
    "mono_metadata_nesting_typedef:\n");

asm(".global mono_metadata_packing_from_typedef\n"
    ".type mono_metadata_packing_from_typedef @function\n"
    "mono_metadata_packing_from_typedef:\n");

asm(".global mono_metadata_parse_array\n"
    ".type mono_metadata_parse_array @function\n"
    "mono_metadata_parse_array:\n");

asm(".global mono_metadata_parse_custom_mod\n"
    ".type mono_metadata_parse_custom_mod @function\n"
    "mono_metadata_parse_custom_mod:\n");

asm(".global mono_metadata_parse_field_type\n"
    ".type mono_metadata_parse_field_type @function\n"
    "mono_metadata_parse_field_type:\n");

asm(".global mono_metadata_parse_marshal_spec\n"
    ".type mono_metadata_parse_marshal_spec @function\n"
    "mono_metadata_parse_marshal_spec:\n");

asm(".global mono_metadata_parse_method_signature\n"
    ".type mono_metadata_parse_method_signature @function\n"
    "mono_metadata_parse_method_signature:\n");

asm(".global mono_metadata_parse_method_signature_full\n"
    ".type mono_metadata_parse_method_signature_full @function\n"
    "mono_metadata_parse_method_signature_full:\n");

asm(".global mono_metadata_parse_mh\n"
    ".type mono_metadata_parse_mh @function\n"
    "mono_metadata_parse_mh:\n");

asm(".global mono_metadata_parse_mh_full\n"
    ".type mono_metadata_parse_mh_full @function\n"
    "mono_metadata_parse_mh_full:\n");

asm(".global mono_metadata_parse_param\n"
    ".type mono_metadata_parse_param @function\n"
    "mono_metadata_parse_param:\n");

asm(".global mono_metadata_parse_signature\n"
    ".type mono_metadata_parse_signature @function\n"
    "mono_metadata_parse_signature:\n");

asm(".global mono_metadata_parse_type\n"
    ".type mono_metadata_parse_type @function\n"
    "mono_metadata_parse_type:\n");

asm(".global mono_metadata_parse_typedef_or_ref\n"
    ".type mono_metadata_parse_typedef_or_ref @function\n"
    "mono_metadata_parse_typedef_or_ref:\n");

asm(".global mono_metadata_properties_from_typedef\n"
    ".type mono_metadata_properties_from_typedef @function\n"
    "mono_metadata_properties_from_typedef:\n");

asm(".global mono_metadata_signature_alloc\n"
    ".type mono_metadata_signature_alloc @function\n"
    "mono_metadata_signature_alloc:\n");

asm(".global mono_metadata_signature_dup\n"
    ".type mono_metadata_signature_dup @function\n"
    "mono_metadata_signature_dup:\n");

asm(".global mono_metadata_signature_equal\n"
    ".type mono_metadata_signature_equal @function\n"
    "mono_metadata_signature_equal:\n");

asm(".global mono_metadata_string_heap\n"
    ".type mono_metadata_string_heap @function\n"
    "mono_metadata_string_heap:\n");

asm(".global mono_metadata_token_from_dor\n"
    ".type mono_metadata_token_from_dor @function\n"
    "mono_metadata_token_from_dor:\n");

asm(".global mono_metadata_translate_token_index\n"
    ".type mono_metadata_translate_token_index @function\n"
    "mono_metadata_translate_token_index:\n");

asm(".global mono_metadata_type_equal\n"
    ".type mono_metadata_type_equal @function\n"
    "mono_metadata_type_equal:\n");

asm(".global mono_metadata_type_hash\n"
    ".type mono_metadata_type_hash @function\n"
    "mono_metadata_type_hash:\n");

asm(".global mono_metadata_typedef_from_field\n"
    ".type mono_metadata_typedef_from_field @function\n"
    "mono_metadata_typedef_from_field:\n");

asm(".global mono_metadata_typedef_from_method\n"
    ".type mono_metadata_typedef_from_method @function\n"
    "mono_metadata_typedef_from_method:\n");

asm(".global mono_metadata_user_string\n"
    ".type mono_metadata_user_string @function\n"
    "mono_metadata_user_string:\n");

asm(".global mono_method_body_get_object\n"
    ".type mono_method_body_get_object @function\n"
    "mono_method_body_get_object:\n");

asm(".global mono_method_can_access_field\n"
    ".type mono_method_can_access_field @function\n"
    "mono_method_can_access_field:\n");

asm(".global mono_method_can_access_method\n"
    ".type mono_method_can_access_method @function\n"
    "mono_method_can_access_method:\n");

asm(".global mono_method_desc_free\n"
    ".type mono_method_desc_free @function\n"
    "mono_method_desc_free:\n");

asm(".global mono_method_desc_from_method\n"
    ".type mono_method_desc_from_method @function\n"
    "mono_method_desc_from_method:\n");

asm(".global mono_method_desc_full_match\n"
    ".type mono_method_desc_full_match @function\n"
    "mono_method_desc_full_match:\n");

asm(".global mono_method_desc_match\n"
    ".type mono_method_desc_match @function\n"
    "mono_method_desc_match:\n");

asm(".global mono_method_desc_new\n"
    ".type mono_method_desc_new @function\n"
    "mono_method_desc_new:\n");

asm(".global mono_method_desc_search_in_class\n"
    ".type mono_method_desc_search_in_class @function\n"
    "mono_method_desc_search_in_class:\n");

asm(".global mono_method_desc_search_in_image\n"
    ".type mono_method_desc_search_in_image @function\n"
    "mono_method_desc_search_in_image:\n");

asm(".global mono_method_full_name\n"
    ".type mono_method_full_name @function\n"
    "mono_method_full_name:\n");

asm(".global mono_method_get_class\n"
    ".type mono_method_get_class @function\n"
    "mono_method_get_class:\n");

asm(".global mono_method_get_flags\n"
    ".type mono_method_get_flags @function\n"
    "mono_method_get_flags:\n");

asm(".global mono_method_get_generic_container\n"
    ".type mono_method_get_generic_container @function\n"
    "mono_method_get_generic_container:\n");

asm(".global mono_method_get_header\n"
    ".type mono_method_get_header @function\n"
    "mono_method_get_header:\n");

asm(".global mono_method_get_header_checked\n"
    ".type mono_method_get_header_checked @function\n"
    "mono_method_get_header_checked:\n");

asm(".global mono_method_get_index\n"
    ".type mono_method_get_index @function\n"
    "mono_method_get_index:\n");

asm(".global mono_method_get_last_managed\n"
    ".type mono_method_get_last_managed @function\n"
    "mono_method_get_last_managed:\n");

asm(".global mono_method_get_marshal_info\n"
    ".type mono_method_get_marshal_info @function\n"
    "mono_method_get_marshal_info:\n");

asm(".global mono_method_get_name\n"
    ".type mono_method_get_name @function\n"
    "mono_method_get_name:\n");

asm(".global mono_method_get_object\n"
    ".type mono_method_get_object @function\n"
    "mono_method_get_object:\n");

asm(".global mono_method_get_param_names\n"
    ".type mono_method_get_param_names @function\n"
    "mono_method_get_param_names:\n");

asm(".global mono_method_get_param_token\n"
    ".type mono_method_get_param_token @function\n"
    "mono_method_get_param_token:\n");

asm(".global mono_method_get_signature\n"
    ".type mono_method_get_signature @function\n"
    "mono_method_get_signature:\n");

asm(".global mono_method_get_signature_full\n"
    ".type mono_method_get_signature_full @function\n"
    "mono_method_get_signature_full:\n");

asm(".global mono_method_get_token\n"
    ".type mono_method_get_token @function\n"
    "mono_method_get_token:\n");

asm(".global mono_method_get_unmanaged_thunk\n"
    ".type mono_method_get_unmanaged_thunk @function\n"
    "mono_method_get_unmanaged_thunk:\n");

asm(".global mono_method_has_marshal_info\n"
    ".type mono_method_has_marshal_info @function\n"
    "mono_method_has_marshal_info:\n");

asm(".global mono_method_header_get_clauses\n"
    ".type mono_method_header_get_clauses @function\n"
    "mono_method_header_get_clauses:\n");

asm(".global mono_method_header_get_code\n"
    ".type mono_method_header_get_code @function\n"
    "mono_method_header_get_code:\n");

asm(".global mono_method_header_get_locals\n"
    ".type mono_method_header_get_locals @function\n"
    "mono_method_header_get_locals:\n");

asm(".global mono_method_header_get_num_clauses\n"
    ".type mono_method_header_get_num_clauses @function\n"
    "mono_method_header_get_num_clauses:\n");

asm(".global mono_method_print_code\n"
    ".type mono_method_print_code @function\n"
    "mono_method_print_code:\n");

asm(".global mono_method_signature\n"
    ".type mono_method_signature @function\n"
    "mono_method_signature:\n");

asm(".global mono_method_verify\n"
    ".type mono_method_verify @function\n"
    "mono_method_verify:\n");

asm(".global mono_mlist_alloc\n"
    ".type mono_mlist_alloc @function\n"
    "mono_mlist_alloc:\n");

asm(".global mono_mlist_append\n"
    ".type mono_mlist_append @function\n"
    "mono_mlist_append:\n");

asm(".global mono_mlist_get_data\n"
    ".type mono_mlist_get_data @function\n"
    "mono_mlist_get_data:\n");

asm(".global mono_mlist_last\n"
    ".type mono_mlist_last @function\n"
    "mono_mlist_last:\n");

asm(".global mono_mlist_length\n"
    ".type mono_mlist_length @function\n"
    "mono_mlist_length:\n");

asm(".global mono_mlist_next\n"
    ".type mono_mlist_next @function\n"
    "mono_mlist_next:\n");

asm(".global mono_mlist_prepend\n"
    ".type mono_mlist_prepend @function\n"
    "mono_mlist_prepend:\n");

asm(".global mono_mlist_remove_item\n"
    ".type mono_mlist_remove_item @function\n"
    "mono_mlist_remove_item:\n");

asm(".global mono_mlist_set_data\n"
    ".type mono_mlist_set_data @function\n"
    "mono_mlist_set_data:\n");

asm(".global mono_mlist_set_next\n"
    ".type mono_mlist_set_next @function\n"
    "mono_mlist_set_next:\n");

asm(".global mono_module_file_get_object\n"
    ".type mono_module_file_get_object @function\n"
    "mono_module_file_get_object:\n");

asm(".global mono_module_get_object\n"
    ".type mono_module_get_object @function\n"
    "mono_module_get_object:\n");

asm(".global mono_monitor_enter\n"
    ".type mono_monitor_enter @function\n"
    "mono_monitor_enter:\n");

asm(".global mono_monitor_enter_v4\n"
    ".type mono_monitor_enter_v4 @function\n"
    "mono_monitor_enter_v4:\n");

asm(".global mono_monitor_exit\n"
    ".type mono_monitor_exit @function\n"
    "mono_monitor_exit:\n");

asm(".global mono_monitor_try_enter\n"
    ".type mono_monitor_try_enter @function\n"
    "mono_monitor_try_enter:\n");

asm(".global mono_mprotect\n"
    ".type mono_mprotect @function\n"
    "mono_mprotect:\n");

asm(".global mono_native_thread_create\n"
    ".type mono_native_thread_create @function\n"
    "mono_native_thread_create:\n");

asm(".global mono_native_thread_id_get\n"
    ".type mono_native_thread_id_get @function\n"
    "mono_native_thread_id_get:\n");

asm(".global mono_native_thread_join\n"
    ".type mono_native_thread_join @function\n"
    "mono_native_thread_join:\n");

asm(".global mono_native_thread_set_name\n"
    ".type mono_native_thread_set_name @function\n"
    "mono_native_thread_set_name:\n");

asm(".global mono_object_castclass_mbyref\n"
    ".type mono_object_castclass_mbyref @function\n"
    "mono_object_castclass_mbyref:\n");

asm(".global mono_object_clone\n"
    ".type mono_object_clone @function\n"
    "mono_object_clone:\n");

asm(".global mono_object_describe\n"
    ".type mono_object_describe @function\n"
    "mono_object_describe:\n");

asm(".global mono_object_describe_fields\n"
    ".type mono_object_describe_fields @function\n"
    "mono_object_describe_fields:\n");

asm(".global mono_object_get_class\n"
    ".type mono_object_get_class @function\n"
    "mono_object_get_class:\n");

asm(".global mono_object_get_domain\n"
    ".type mono_object_get_domain @function\n"
    "mono_object_get_domain:\n");

asm(".global mono_object_get_size\n"
    ".type mono_object_get_size @function\n"
    "mono_object_get_size:\n");

asm(".global mono_object_get_virtual_method\n"
    ".type mono_object_get_virtual_method @function\n"
    "mono_object_get_virtual_method:\n");

asm(".global mono_object_hash\n"
    ".type mono_object_hash @function\n"
    "mono_object_hash:\n");

asm(".global mono_object_isinst\n"
    ".type mono_object_isinst @function\n"
    "mono_object_isinst:\n");

asm(".global mono_object_isinst_mbyref\n"
    ".type mono_object_isinst_mbyref @function\n"
    "mono_object_isinst_mbyref:\n");

asm(".global mono_object_new\n"
    ".type mono_object_new @function\n"
    "mono_object_new:\n");

asm(".global mono_object_new_alloc_specific\n"
    ".type mono_object_new_alloc_specific @function\n"
    "mono_object_new_alloc_specific:\n");

asm(".global mono_object_new_fast\n"
    ".type mono_object_new_fast @function\n"
    "mono_object_new_fast:\n");

asm(".global mono_object_new_from_token\n"
    ".type mono_object_new_from_token @function\n"
    "mono_object_new_from_token:\n");

asm(".global mono_object_new_specific\n"
    ".type mono_object_new_specific @function\n"
    "mono_object_new_specific:\n");

asm(".global mono_object_to_string\n"
    ".type mono_object_to_string @function\n"
    "mono_object_to_string:\n");

asm(".global mono_object_unbox\n"
    ".type mono_object_unbox @function\n"
    "mono_object_unbox:\n");

asm(".global mono_opcode_name\n"
    ".type mono_opcode_name @function\n"
    "mono_opcode_name:\n");

asm(".global mono_opcode_value\n"
    ".type mono_opcode_value @function\n"
    "mono_opcode_value:\n");

asm(".global mono_pagesize\n"
    ".type mono_pagesize @function\n"
    "mono_pagesize:\n");

asm(".global mono_param_get_objects\n"
    ".type mono_param_get_objects @function\n"
    "mono_param_get_objects:\n");

asm(".global mono_parse_default_optimizations\n"
    ".type mono_parse_default_optimizations @function\n"
    "mono_parse_default_optimizations:\n");

asm(".global mono_parse_env_options\n"
    ".type mono_parse_env_options @function\n"
    "mono_parse_env_options:\n");

asm(".global mono_parse_options_from\n"
    ".type mono_parse_options_from @function\n"
    "mono_parse_options_from:\n");

asm(".global mono_path_canonicalize\n"
    ".type mono_path_canonicalize @function\n"
    "mono_path_canonicalize:\n");

asm(".global mono_path_resolve_symlinks\n"
    ".type mono_path_resolve_symlinks @function\n"
    "mono_path_resolve_symlinks:\n");

asm(".global mono_pe_file_open\n"
    ".type mono_pe_file_open @function\n"
    "mono_pe_file_open:\n");

asm(".global mono_perfcounter_foreach\n"
    ".type mono_perfcounter_foreach @function\n"
    "mono_perfcounter_foreach:\n");

asm(".global mono_perfcounters_init\n"
    ".type mono_perfcounters_init @function\n"
    "mono_perfcounters_init:\n");

asm(".global mono_personality\n"
    ".type mono_personality @function\n"
    "mono_personality:\n");

asm(".global mono_pmip\n"
    ".type mono_pmip @function\n"
    "mono_pmip:\n");

asm(".global mono_poll\n"
    ".type mono_poll @function\n"
    "mono_poll:\n");

asm(".global mono_print_method_from_ip\n"
    ".type mono_print_method_from_ip @function\n"
    "mono_print_method_from_ip:\n");

asm(".global mono_print_thread_dump\n"
    ".type mono_print_thread_dump @function\n"
    "mono_print_thread_dump:\n");

asm(".global mono_print_thread_dump_from_ctx\n"
    ".type mono_print_thread_dump_from_ctx @function\n"
    "mono_print_thread_dump_from_ctx:\n");

asm(".global mono_print_unhandled_exception\n"
    ".type mono_print_unhandled_exception @function\n"
    "mono_print_unhandled_exception:\n");

asm(".global mono_profiler_install\n"
    ".type mono_profiler_install @function\n"
    "mono_profiler_install:\n");

asm(".global mono_profiler_install_allocation\n"
    ".type mono_profiler_install_allocation @function\n"
    "mono_profiler_install_allocation:\n");

asm(".global mono_profiler_install_enter_leave\n"
    ".type mono_profiler_install_enter_leave @function\n"
    "mono_profiler_install_enter_leave:\n");

asm(".global mono_profiler_install_exception\n"
    ".type mono_profiler_install_exception @function\n"
    "mono_profiler_install_exception:\n");

asm(".global mono_profiler_install_gc\n"
    ".type mono_profiler_install_gc @function\n"
    "mono_profiler_install_gc:\n");

asm(".global mono_profiler_install_jit_end\n"
    ".type mono_profiler_install_jit_end @function\n"
    "mono_profiler_install_jit_end:\n");

asm(".global mono_profiler_install_thread\n"
    ".type mono_profiler_install_thread @function\n"
    "mono_profiler_install_thread:\n");

asm(".global mono_profiler_load\n"
    ".type mono_profiler_load @function\n"
    "mono_profiler_load:\n");

asm(".global mono_profiler_set_events\n"
    ".type mono_profiler_set_events @function\n"
    "mono_profiler_set_events:\n");

asm(".global mono_property_get_flags\n"
    ".type mono_property_get_flags @function\n"
    "mono_property_get_flags:\n");

asm(".global mono_property_get_get_method\n"
    ".type mono_property_get_get_method @function\n"
    "mono_property_get_get_method:\n");

asm(".global mono_property_get_name\n"
    ".type mono_property_get_name @function\n"
    "mono_property_get_name:\n");

asm(".global mono_property_get_object\n"
    ".type mono_property_get_object @function\n"
    "mono_property_get_object:\n");

asm(".global mono_property_get_parent\n"
    ".type mono_property_get_parent @function\n"
    "mono_property_get_parent:\n");

asm(".global mono_property_get_set_method\n"
    ".type mono_property_get_set_method @function\n"
    "mono_property_get_set_method:\n");

asm(".global mono_property_get_value\n"
    ".type mono_property_get_value @function\n"
    "mono_property_get_value:\n");

asm(".global mono_property_hash_destroy\n"
    ".type mono_property_hash_destroy @function\n"
    "mono_property_hash_destroy:\n");

asm(".global mono_property_hash_insert\n"
    ".type mono_property_hash_insert @function\n"
    "mono_property_hash_insert:\n");

asm(".global mono_property_hash_lookup\n"
    ".type mono_property_hash_lookup @function\n"
    "mono_property_hash_lookup:\n");

asm(".global mono_property_hash_new\n"
    ".type mono_property_hash_new @function\n"
    "mono_property_hash_new:\n");

asm(".global mono_property_hash_remove_object\n"
    ".type mono_property_hash_remove_object @function\n"
    "mono_property_hash_remove_object:\n");

asm(".global mono_property_set_value\n"
    ".type mono_property_set_value @function\n"
    "mono_property_set_value:\n");

asm(".global mono_ptr_class_get\n"
    ".type mono_ptr_class_get @function\n"
    "mono_ptr_class_get:\n");

asm(".global mono_raise_exception\n"
    ".type mono_raise_exception @function\n"
    "mono_raise_exception:\n");

asm(".global mono_reflection_assembly_get_assembly\n"
    ".type mono_reflection_assembly_get_assembly @function\n"
    "mono_reflection_assembly_get_assembly:\n");

asm(".global mono_reflection_free_type_info\n"
    ".type mono_reflection_free_type_info @function\n"
    "mono_reflection_free_type_info:\n");

asm(".global mono_reflection_get_custom_attrs\n"
    ".type mono_reflection_get_custom_attrs @function\n"
    "mono_reflection_get_custom_attrs:\n");

asm(".global mono_reflection_get_custom_attrs_blob\n"
    ".type mono_reflection_get_custom_attrs_blob @function\n"
    "mono_reflection_get_custom_attrs_blob:\n");

asm(".global mono_reflection_get_custom_attrs_by_type\n"
    ".type mono_reflection_get_custom_attrs_by_type @function\n"
    "mono_reflection_get_custom_attrs_by_type:\n");

asm(".global mono_reflection_get_custom_attrs_data\n"
    ".type mono_reflection_get_custom_attrs_data @function\n"
    "mono_reflection_get_custom_attrs_data:\n");

asm(".global mono_reflection_get_custom_attrs_info\n"
    ".type mono_reflection_get_custom_attrs_info @function\n"
    "mono_reflection_get_custom_attrs_info:\n");

asm(".global mono_reflection_get_token\n"
    ".type mono_reflection_get_token @function\n"
    "mono_reflection_get_token:\n");

asm(".global mono_reflection_get_type\n"
    ".type mono_reflection_get_type @function\n"
    "mono_reflection_get_type:\n");

asm(".global mono_reflection_parse_type\n"
    ".type mono_reflection_parse_type @function\n"
    "mono_reflection_parse_type:\n");

asm(".global mono_reflection_type_from_name\n"
    ".type mono_reflection_type_from_name @function\n"
    "mono_reflection_type_from_name:\n");

asm(".global mono_reflection_type_get_type\n"
    ".type mono_reflection_type_get_type @function\n"
    "mono_reflection_type_get_type:\n");

asm(".global mono_register_bundled_assemblies\n"
    ".type mono_register_bundled_assemblies @function\n"
    "mono_register_bundled_assemblies:\n");

asm(".global mono_register_config_for_assembly\n"
    ".type mono_register_config_for_assembly @function\n"
    "mono_register_config_for_assembly:\n");

asm(".global mono_register_machine_config\n"
    ".type mono_register_machine_config @function\n"
    "mono_register_machine_config:\n");

asm(".global mono_register_symfile_for_assembly\n"
    ".type mono_register_symfile_for_assembly @function\n"
    "mono_register_symfile_for_assembly:\n");

asm(".global mono_runtime_class_init\n"
    ".type mono_runtime_class_init @function\n"
    "mono_runtime_class_init:\n");

asm(".global mono_runtime_cleanup\n"
    ".type mono_runtime_cleanup @function\n"
    "mono_runtime_cleanup:\n");

asm(".global mono_runtime_delegate_invoke\n"
    ".type mono_runtime_delegate_invoke @function\n"
    "mono_runtime_delegate_invoke:\n");

asm(".global mono_runtime_exec_main\n"
    ".type mono_runtime_exec_main @function\n"
    "mono_runtime_exec_main:\n");

asm(".global mono_runtime_exec_managed_code\n"
    ".type mono_runtime_exec_managed_code @function\n"
    "mono_runtime_exec_managed_code:\n");

asm(".global mono_runtime_get_main_args\n"
    ".type mono_runtime_get_main_args @function\n"
    "mono_runtime_get_main_args:\n");

asm(".global mono_runtime_init\n"
    ".type mono_runtime_init @function\n"
    "mono_runtime_init:\n");

asm(".global mono_runtime_invoke\n"
    ".type mono_runtime_invoke @function\n"
    "mono_runtime_invoke:\n");

asm(".global mono_runtime_invoke_array\n"
    ".type mono_runtime_invoke_array @function\n"
    "mono_runtime_invoke_array:\n");

asm(".global mono_runtime_is_shutting_down\n"
    ".type mono_runtime_is_shutting_down @function\n"
    "mono_runtime_is_shutting_down:\n");

asm(".global mono_runtime_object_init\n"
    ".type mono_runtime_object_init @function\n"
    "mono_runtime_object_init:\n");

asm(".global mono_runtime_quit\n"
    ".type mono_runtime_quit @function\n"
    "mono_runtime_quit:\n");

asm(".global mono_runtime_resource_check_limit\n"
    ".type mono_runtime_resource_check_limit @function\n"
    "mono_runtime_resource_check_limit:\n");

asm(".global mono_runtime_resource_limit\n"
    ".type mono_runtime_resource_limit @function\n"
    "mono_runtime_resource_limit:\n");

asm(".global mono_runtime_resource_set_callback\n"
    ".type mono_runtime_resource_set_callback @function\n"
    "mono_runtime_resource_set_callback:\n");

asm(".global mono_runtime_run_main\n"
    ".type mono_runtime_run_main @function\n"
    "mono_runtime_run_main:\n");

asm(".global mono_runtime_set_main_args\n"
    ".type mono_runtime_set_main_args @function\n"
    "mono_runtime_set_main_args:\n");

asm(".global mono_runtime_set_shutting_down\n"
    ".type mono_runtime_set_shutting_down @function\n"
    "mono_runtime_set_shutting_down:\n");

asm(".global mono_security_core_clr_get_options\n"
    ".type mono_security_core_clr_get_options @function\n"
    "mono_security_core_clr_get_options:\n");

asm(".global mono_security_core_clr_require_elevated_permissions\n"
    ".type mono_security_core_clr_require_elevated_permissions @function\n"
    "mono_security_core_clr_require_elevated_permissions:\n");

asm(".global mono_security_core_clr_set_options\n"
    ".type mono_security_core_clr_set_options @function\n"
    "mono_security_core_clr_set_options:\n");

asm(".global mono_security_enable_core_clr\n"
    ".type mono_security_enable_core_clr @function\n"
    "mono_security_enable_core_clr:\n");

asm(".global mono_security_set_core_clr_platform_callback\n"
    ".type mono_security_set_core_clr_platform_callback @function\n"
    "mono_security_set_core_clr_platform_callback:\n");

asm(".global mono_set_allocator_vtable\n"
    ".type mono_set_allocator_vtable @function\n"
    "mono_set_allocator_vtable:\n");

asm(".global mono_set_assemblies_path\n"
    ".type mono_set_assemblies_path @function\n"
    "mono_set_assemblies_path:\n");

asm(".global mono_set_break_policy\n"
    ".type mono_set_break_policy @function\n"
    "mono_set_break_policy:\n");

asm(".global mono_set_config_dir\n"
    ".type mono_set_config_dir @function\n"
    "mono_set_config_dir:\n");

asm(".global mono_set_crash_chaining\n"
    ".type mono_set_crash_chaining @function\n"
    "mono_set_crash_chaining:\n");

asm(".global mono_set_defaults\n"
    ".type mono_set_defaults @function\n"
    "mono_set_defaults:\n");

asm(".global mono_set_dirs\n"
    ".type mono_set_dirs @function\n"
    "mono_set_dirs:\n");

asm(".global mono_set_is_debugger_attached\n"
    ".type mono_set_is_debugger_attached @function\n"
    "mono_set_is_debugger_attached:\n");

asm(".global mono_set_rootdir\n"
    ".type mono_set_rootdir @function\n"
    "mono_set_rootdir:\n");

asm(".global mono_set_signal_chaining\n"
    ".type mono_set_signal_chaining @function\n"
    "mono_set_signal_chaining:\n");

asm(".global mono_sgen_set_thread_type\n"
    ".type mono_sgen_set_thread_type @function\n"
    "mono_sgen_set_thread_type:\n");

asm(".global mono_sha1_final\n"
    ".type mono_sha1_final @function\n"
    "mono_sha1_final:\n");

asm(".global mono_sha1_get_digest\n"
    ".type mono_sha1_get_digest @function\n"
    "mono_sha1_get_digest:\n");

asm(".global mono_sha1_get_digest_from_file\n"
    ".type mono_sha1_get_digest_from_file @function\n"
    "mono_sha1_get_digest_from_file:\n");

asm(".global mono_sha1_init\n"
    ".type mono_sha1_init @function\n"
    "mono_sha1_init:\n");

asm(".global mono_sha1_update\n"
    ".type mono_sha1_update @function\n"
    "mono_sha1_update:\n");

asm(".global mono_shared_area\n"
    ".type mono_shared_area @function\n"
    "mono_shared_area:\n");

asm(".global mono_shared_area_for_pid\n"
    ".type mono_shared_area_for_pid @function\n"
    "mono_shared_area_for_pid:\n");

asm(".global mono_shared_area_instances\n"
    ".type mono_shared_area_instances @function\n"
    "mono_shared_area_instances:\n");

asm(".global mono_shared_area_remove\n"
    ".type mono_shared_area_remove @function\n"
    "mono_shared_area_remove:\n");

asm(".global mono_shared_area_unload\n"
    ".type mono_shared_area_unload @function\n"
    "mono_shared_area_unload:\n");

asm(".global mono_signature_explicit_this\n"
    ".type mono_signature_explicit_this @function\n"
    "mono_signature_explicit_this:\n");

asm(".global mono_signature_get_call_conv\n"
    ".type mono_signature_get_call_conv @function\n"
    "mono_signature_get_call_conv:\n");

asm(".global mono_signature_get_desc\n"
    ".type mono_signature_get_desc @function\n"
    "mono_signature_get_desc:\n");

asm(".global mono_signature_get_param_count\n"
    ".type mono_signature_get_param_count @function\n"
    "mono_signature_get_param_count:\n");

asm(".global mono_signature_get_params\n"
    ".type mono_signature_get_params @function\n"
    "mono_signature_get_params:\n");

asm(".global mono_signature_get_return_type\n"
    ".type mono_signature_get_return_type @function\n"
    "mono_signature_get_return_type:\n");

asm(".global mono_signature_hash\n"
    ".type mono_signature_hash @function\n"
    "mono_signature_hash:\n");

asm(".global mono_signature_is_instance\n"
    ".type mono_signature_is_instance @function\n"
    "mono_signature_is_instance:\n");

asm(".global mono_signature_param_is_out\n"
    ".type mono_signature_param_is_out @function\n"
    "mono_signature_param_is_out:\n");

asm(".global mono_signature_vararg_start\n"
    ".type mono_signature_vararg_start @function\n"
    "mono_signature_vararg_start:\n");

asm(".global mono_signbit_double\n"
    ".type mono_signbit_double @function\n"
    "mono_signbit_double:\n");

asm(".global mono_signbit_float\n"
    ".type mono_signbit_float @function\n"
    "mono_signbit_float:\n");

asm(".global mono_stack_walk\n"
    ".type mono_stack_walk @function\n"
    "mono_stack_walk:\n");

asm(".global mono_stack_walk_async_safe\n"
    ".type mono_stack_walk_async_safe @function\n"
    "mono_stack_walk_async_safe:\n");

asm(".global mono_stack_walk_no_il\n"
    ".type mono_stack_walk_no_il @function\n"
    "mono_stack_walk_no_il:\n");

asm(".global mono_string_chars\n"
    ".type mono_string_chars @function\n"
    "mono_string_chars:\n");

asm(".global mono_string_empty\n"
    ".type mono_string_empty @function\n"
    "mono_string_empty:\n");

asm(".global mono_string_empty_wrapper\n"
    ".type mono_string_empty_wrapper @function\n"
    "mono_string_empty_wrapper:\n");

asm(".global mono_string_equal\n"
    ".type mono_string_equal @function\n"
    "mono_string_equal:\n");

asm(".global mono_string_from_bstr\n"
    ".type mono_string_from_bstr @function\n"
    "mono_string_from_bstr:\n");

asm(".global mono_string_from_utf16\n"
    ".type mono_string_from_utf16 @function\n"
    "mono_string_from_utf16:\n");

asm(".global mono_string_from_utf32\n"
    ".type mono_string_from_utf32 @function\n"
    "mono_string_from_utf32:\n");

asm(".global mono_string_hash\n"
    ".type mono_string_hash @function\n"
    "mono_string_hash:\n");

asm(".global mono_string_intern\n"
    ".type mono_string_intern @function\n"
    "mono_string_intern:\n");

asm(".global mono_string_is_interned\n"
    ".type mono_string_is_interned @function\n"
    "mono_string_is_interned:\n");

asm(".global mono_string_length\n"
    ".type mono_string_length @function\n"
    "mono_string_length:\n");

asm(".global mono_string_new\n"
    ".type mono_string_new @function\n"
    "mono_string_new:\n");

asm(".global mono_string_new_len\n"
    ".type mono_string_new_len @function\n"
    "mono_string_new_len:\n");

asm(".global mono_string_new_size\n"
    ".type mono_string_new_size @function\n"
    "mono_string_new_size:\n");

asm(".global mono_string_new_utf16\n"
    ".type mono_string_new_utf16 @function\n"
    "mono_string_new_utf16:\n");

asm(".global mono_string_new_utf32\n"
    ".type mono_string_new_utf32 @function\n"
    "mono_string_new_utf32:\n");

asm(".global mono_string_new_wrapper\n"
    ".type mono_string_new_wrapper @function\n"
    "mono_string_new_wrapper:\n");

asm(".global mono_string_to_utf16\n"
    ".type mono_string_to_utf16 @function\n"
    "mono_string_to_utf16:\n");

asm(".global mono_string_to_utf32\n"
    ".type mono_string_to_utf32 @function\n"
    "mono_string_to_utf32:\n");

asm(".global mono_string_to_utf8\n"
    ".type mono_string_to_utf8 @function\n"
    "mono_string_to_utf8:\n");

asm(".global mono_string_to_utf8_checked\n"
    ".type mono_string_to_utf8_checked @function\n"
    "mono_string_to_utf8_checked:\n");

asm(".global mono_stringify_assembly_name\n"
    ".type mono_stringify_assembly_name @function\n"
    "mono_stringify_assembly_name:\n");

asm(".global mono_table_info_get_rows\n"
    ".type mono_table_info_get_rows @function\n"
    "mono_table_info_get_rows:\n");

asm(".global mono_thread_attach\n"
    ".type mono_thread_attach @function\n"
    "mono_thread_attach:\n");

asm(".global mono_thread_cleanup\n"
    ".type mono_thread_cleanup @function\n"
    "mono_thread_cleanup:\n");

asm(".global mono_thread_create\n"
    ".type mono_thread_create @function\n"
    "mono_thread_create:\n");

asm(".global mono_thread_current\n"
    ".type mono_thread_current @function\n"
    "mono_thread_current:\n");

asm(".global mono_thread_detach\n"
    ".type mono_thread_detach @function\n"
    "mono_thread_detach:\n");

asm(".global mono_thread_detach_if_exiting\n"
    ".type mono_thread_detach_if_exiting @function\n"
    "mono_thread_detach_if_exiting:\n");

asm(".global mono_thread_exit\n"
    ".type mono_thread_exit @function\n"
    "mono_thread_exit:\n");

asm(".global mono_thread_get_main\n"
    ".type mono_thread_get_main @function\n"
    "mono_thread_get_main:\n");

asm(".global mono_thread_get_managed_id\n"
    ".type mono_thread_get_managed_id @function\n"
    "mono_thread_get_managed_id:\n");

asm(".global mono_thread_get_max_threads\n"
    ".type mono_thread_get_max_threads @function\n"
    "mono_thread_get_max_threads:\n");

asm(".global mono_thread_get_name_utf8\n"
    ".type mono_thread_get_name_utf8 @function\n"
    "mono_thread_get_name_utf8:\n");

asm(".global mono_thread_get_num_threads\n"
    ".type mono_thread_get_num_threads @function\n"
    "mono_thread_get_num_threads:\n");

asm(".global mono_thread_get_undeniable_exception\n"
    ".type mono_thread_get_undeniable_exception @function\n"
    "mono_thread_get_undeniable_exception:\n");

asm(".global mono_thread_hazardous_queue_free\n"
    ".type mono_thread_hazardous_queue_free @function\n"
    "mono_thread_hazardous_queue_free:\n");

asm(".global mono_thread_hazardous_try_free\n"
    ".type mono_thread_hazardous_try_free @function\n"
    "mono_thread_hazardous_try_free:\n");

asm(".global mono_thread_hazardous_try_free_all\n"
    ".type mono_thread_hazardous_try_free_all @function\n"
    "mono_thread_hazardous_try_free_all:\n");

asm(".global mono_thread_info_detach\n"
    ".type mono_thread_info_detach @function\n"
    "mono_thread_info_detach:\n");

asm(".global mono_thread_info_yield\n"
    ".type mono_thread_info_yield @function\n"
    "mono_thread_info_yield:\n");

asm(".global mono_thread_init\n"
    ".type mono_thread_init @function\n"
    "mono_thread_init:\n");

asm(".global mono_thread_is_foreign\n"
    ".type mono_thread_is_foreign @function\n"
    "mono_thread_is_foreign:\n");

asm(".global mono_thread_manage\n"
    ".type mono_thread_manage @function\n"
    "mono_thread_manage:\n");

asm(".global mono_thread_new_init\n"
    ".type mono_thread_new_init @function\n"
    "mono_thread_new_init:\n");

asm(".global mono_thread_set_main\n"
    ".type mono_thread_set_main @function\n"
    "mono_thread_set_main:\n");

asm(".global mono_thread_set_manage_callback\n"
    ".type mono_thread_set_manage_callback @function\n"
    "mono_thread_set_manage_callback:\n");

asm(".global mono_thread_set_max_threads\n"
    ".type mono_thread_set_max_threads @function\n"
    "mono_thread_set_max_threads:\n");

asm(".global mono_thread_set_threads_exhausted_callback\n"
    ".type mono_thread_set_threads_exhausted_callback @function\n"
    "mono_thread_set_threads_exhausted_callback:\n");

asm(".global mono_thread_stop\n"
    ".type mono_thread_stop @function\n"
    "mono_thread_stop:\n");

asm(".global mono_thread_suspend_all_other_threads\n"
    ".type mono_thread_suspend_all_other_threads @function\n"
    "mono_thread_suspend_all_other_threads:\n");

asm(".global mono_threadpool_set_max_threads\n"
    ".type mono_threadpool_set_max_threads @function\n"
    "mono_threadpool_set_max_threads:\n");

asm(".global mono_threads_assert_gc_safe_region\n"
    ".type mono_threads_assert_gc_safe_region @function\n"
    "mono_threads_assert_gc_safe_region:\n");

asm(".global mono_threads_assert_gc_unsafe_region\n"
    ".type mono_threads_assert_gc_unsafe_region @function\n"
    "mono_threads_assert_gc_unsafe_region:\n");

asm(".global mono_threads_attach_coop\n"
    ".type mono_threads_attach_coop @function\n"
    "mono_threads_attach_coop:\n");

asm(".global mono_threads_attach_tools_thread\n"
    ".type mono_threads_attach_tools_thread @function\n"
    "mono_threads_attach_tools_thread:\n");

asm(".global mono_threads_detach_coop\n"
    ".type mono_threads_detach_coop @function\n"
    "mono_threads_detach_coop:\n");

asm(".global mono_threads_enter_gc_safe_region\n"
    ".type mono_threads_enter_gc_safe_region @function\n"
    "mono_threads_enter_gc_safe_region:\n");

asm(".global mono_threads_enter_gc_safe_region_unbalanced\n"
    ".type mono_threads_enter_gc_safe_region_unbalanced @function\n"
    "mono_threads_enter_gc_safe_region_unbalanced:\n");

asm(".global mono_threads_enter_gc_unsafe_region\n"
    ".type mono_threads_enter_gc_unsafe_region @function\n"
    "mono_threads_enter_gc_unsafe_region:\n");

asm(".global mono_threads_enter_gc_unsafe_region_unbalanced\n"
    ".type mono_threads_enter_gc_unsafe_region_unbalanced @function\n"
    "mono_threads_enter_gc_unsafe_region_unbalanced:\n");

asm(".global mono_threads_exit_gc_safe_region\n"
    ".type mono_threads_exit_gc_safe_region @function\n"
    "mono_threads_exit_gc_safe_region:\n");

asm(".global mono_threads_exit_gc_safe_region_unbalanced\n"
    ".type mono_threads_exit_gc_safe_region_unbalanced @function\n"
    "mono_threads_exit_gc_safe_region_unbalanced:\n");

asm(".global mono_threads_exit_gc_unsafe_region\n"
    ".type mono_threads_exit_gc_unsafe_region @function\n"
    "mono_threads_exit_gc_unsafe_region:\n");

asm(".global mono_threads_exit_gc_unsafe_region_unbalanced\n"
    ".type mono_threads_exit_gc_unsafe_region_unbalanced @function\n"
    "mono_threads_exit_gc_unsafe_region_unbalanced:\n");

asm(".global mono_threads_get_default_stacksize\n"
    ".type mono_threads_get_default_stacksize @function\n"
    "mono_threads_get_default_stacksize:\n");

asm(".global mono_threads_request_thread_dump\n"
    ".type mono_threads_request_thread_dump @function\n"
    "mono_threads_request_thread_dump:\n");

asm(".global mono_threads_set_default_stacksize\n"
    ".type mono_threads_set_default_stacksize @function\n"
    "mono_threads_set_default_stacksize:\n");

asm(".global mono_threads_set_shutting_down\n"
    ".type mono_threads_set_shutting_down @function\n"
    "mono_threads_set_shutting_down:\n");

asm(".global mono_trace_set_level_string\n"
    ".type mono_trace_set_level_string @function\n"
    "mono_trace_set_level_string:\n");

asm(".global mono_trace_set_log_handler\n"
    ".type mono_trace_set_log_handler @function\n"
    "mono_trace_set_log_handler:\n");

asm(".global mono_trace_set_logdest_string\n"
    ".type mono_trace_set_logdest_string @function\n"
    "mono_trace_set_logdest_string:\n");

asm(".global mono_trace_set_logheader_string\n"
    ".type mono_trace_set_logheader_string @function\n"
    "mono_trace_set_logheader_string:\n");

asm(".global mono_trace_set_mask_string\n"
    ".type mono_trace_set_mask_string @function\n"
    "mono_trace_set_mask_string:\n");

asm(".global mono_trace_set_print_handler\n"
    ".type mono_trace_set_print_handler @function\n"
    "mono_trace_set_print_handler:\n");

asm(".global mono_trace_set_printerr_handler\n"
    ".type mono_trace_set_printerr_handler @function\n"
    "mono_trace_set_printerr_handler:\n");

asm(".global mono_type_create_from_typespec\n"
    ".type mono_type_create_from_typespec @function\n"
    "mono_type_create_from_typespec:\n");

asm(".global mono_type_full_name\n"
    ".type mono_type_full_name @function\n"
    "mono_type_full_name:\n");

asm(".global mono_type_generic_inst_is_valuetype\n"
    ".type mono_type_generic_inst_is_valuetype @function\n"
    "mono_type_generic_inst_is_valuetype:\n");

asm(".global mono_type_get_array_type\n"
    ".type mono_type_get_array_type @function\n"
    "mono_type_get_array_type:\n");

asm(".global mono_type_get_class\n"
    ".type mono_type_get_class @function\n"
    "mono_type_get_class:\n");

asm(".global mono_type_get_desc\n"
    ".type mono_type_get_desc @function\n"
    "mono_type_get_desc:\n");

asm(".global mono_type_get_modifiers\n"
    ".type mono_type_get_modifiers @function\n"
    "mono_type_get_modifiers:\n");

asm(".global mono_type_get_name\n"
    ".type mono_type_get_name @function\n"
    "mono_type_get_name:\n");

asm(".global mono_type_get_object\n"
    ".type mono_type_get_object @function\n"
    "mono_type_get_object:\n");

asm(".global mono_type_get_ptr_type\n"
    ".type mono_type_get_ptr_type @function\n"
    "mono_type_get_ptr_type:\n");

asm(".global mono_type_get_signature\n"
    ".type mono_type_get_signature @function\n"
    "mono_type_get_signature:\n");

asm(".global mono_type_get_type\n"
    ".type mono_type_get_type @function\n"
    "mono_type_get_type:\n");

asm(".global mono_type_get_underlying_type\n"
    ".type mono_type_get_underlying_type @function\n"
    "mono_type_get_underlying_type:\n");

asm(".global mono_type_is_byref\n"
    ".type mono_type_is_byref @function\n"
    "mono_type_is_byref:\n");

asm(".global mono_type_is_pointer\n"
    ".type mono_type_is_pointer @function\n"
    "mono_type_is_pointer:\n");

asm(".global mono_type_is_reference\n"
    ".type mono_type_is_reference @function\n"
    "mono_type_is_reference:\n");

asm(".global mono_type_is_struct\n"
    ".type mono_type_is_struct @function\n"
    "mono_type_is_struct:\n");

asm(".global mono_type_is_valid_enum_basetype\n"
    ".type mono_type_is_valid_enum_basetype @function\n"
    "mono_type_is_valid_enum_basetype:\n");

asm(".global mono_type_is_void\n"
    ".type mono_type_is_void @function\n"
    "mono_type_is_void:\n");

asm(".global mono_type_size\n"
    ".type mono_type_size @function\n"
    "mono_type_size:\n");

asm(".global mono_type_stack_size\n"
    ".type mono_type_stack_size @function\n"
    "mono_type_stack_size:\n");

asm(".global mono_type_to_unmanaged\n"
    ".type mono_type_to_unmanaged @function\n"
    "mono_type_to_unmanaged:\n");

asm(".global mono_unhandled_exception\n"
    ".type mono_unhandled_exception @function\n"
    "mono_unhandled_exception:\n");

asm(".global mono_unhandled_exception_message\n"
    ".type mono_unhandled_exception_message @function\n"
    "mono_unhandled_exception_message:\n");

asm(".global mono_unicode_from_external\n"
    ".type mono_unicode_from_external @function\n"
    "mono_unicode_from_external:\n");

asm(".global mono_unicode_to_external\n"
    ".type mono_unicode_to_external @function\n"
    "mono_unicode_to_external:\n");

asm(".global mono_utf8_from_external\n"
    ".type mono_utf8_from_external @function\n"
    "mono_utf8_from_external:\n");

asm(".global mono_utf8_validate_and_len\n"
    ".type mono_utf8_validate_and_len @function\n"
    "mono_utf8_validate_and_len:\n");

asm(".global mono_utf8_validate_and_len_with_bounds\n"
    ".type mono_utf8_validate_and_len_with_bounds @function\n"
    "mono_utf8_validate_and_len_with_bounds:\n");

asm(".global mono_valloc\n"
    ".type mono_valloc @function\n"
    "mono_valloc:\n");

asm(".global mono_valloc_aligned\n"
    ".type mono_valloc_aligned @function\n"
    "mono_valloc_aligned:\n");

asm(".global mono_value_box\n"
    ".type mono_value_box @function\n"
    "mono_value_box:\n");

asm(".global mono_value_copy\n"
    ".type mono_value_copy @function\n"
    "mono_value_copy:\n");

asm(".global mono_value_copy_array\n"
    ".type mono_value_copy_array @function\n"
    "mono_value_copy_array:\n");

asm(".global mono_value_describe_fields\n"
    ".type mono_value_describe_fields @function\n"
    "mono_value_describe_fields:\n");

asm(".global mono_verify_corlib\n"
    ".type mono_verify_corlib @function\n"
    "mono_verify_corlib:\n");

asm(".global mono_vfree\n"
    ".type mono_vfree @function\n"
    "mono_vfree:\n");

asm(".global mono_vtable_get_static_field_data\n"
    ".type mono_vtable_get_static_field_data @function\n"
    "mono_vtable_get_static_field_data:\n");

asm(".global mono_win32_compat_CopyMemory\n"
    ".type mono_win32_compat_CopyMemory @function\n"
    "mono_win32_compat_CopyMemory:\n");

asm(".global mono_win32_compat_FillMemory\n"
    ".type mono_win32_compat_FillMemory @function\n"
    "mono_win32_compat_FillMemory:\n");

asm(".global mono_win32_compat_MoveMemory\n"
    ".type mono_win32_compat_MoveMemory @function\n"
    "mono_win32_compat_MoveMemory:\n");

asm(".global mono_win32_compat_ZeroMemory\n"
    ".type mono_win32_compat_ZeroMemory @function\n"
    "mono_win32_compat_ZeroMemory:\n");

asm(".global pss_io_icall_install_functions\n"
    ".type pss_io_icall_install_functions @function\n"
    "pss_io_icall_install_functions:\n");

asm(".global mono_build_date\n"
    ".type   mono_build_date, @object\n"
    "mono_build_date:\n");
