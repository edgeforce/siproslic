# This file is used to update compiler options and generate A51 files for 
# device specific application examples.
# If these parameters are changed, you can use this script to re-generate them.
#
#   1. compiler options          options for assembler/compiler/linker 
#                                (See the config variabls below)
#   2. A51 file                  address of USBXpress library and code
#                                rage ...
#                                If A51 files in USB_Bootloader_Firmware_Source\Auto_gen_BL_HEX 
#                                are changed, you need run this script
#
#
# Compiling setting of application example code
set COMP_OPTION(ASM)      "XR GEN DB EP INCDIR(C:\\SiLabs\\MCU\\Inc)"
set COMP_OPTION(C)        "DB OE BR INTVECTOR(0x1400) INTERVAL(3) INCDIR(C:\\SiLabs\\MCU\\Inc)"
set COMP_OPTION_LINK(F320_1)       "RS(256) PL(68) PW(78) CODE(0x1400-0x3BFD)"  ;# 16K
set COMP_OPTION_LINK(F326_7)       "RS(256) PL(68) PW(78) CODE(0x1400-0x3BFD)"  ;# 16K
set COMP_OPTION_LINK(F34x_64k)     "RS(256) PL(68) PW(78) CODE(0x1400-0xF9FD)"
set COMP_OPTION_LINK(F34x_32k)     "RS(256) PL(68) PW(78) CODE(0x1400-0x7DFD)"
set COMP_OPTION_LINK(F38x_64k)     "RS(256) PL(68) PW(78) CODE(0x1400-0xF9FD)"
set COMP_OPTION_LINK(F38x_32k)     "RS(256) PL(68) PW(78) CODE(0x1400-0x7DFD)"



# Setting of folder name
set USR_PROJ_PREF         "..\\Device_Specific\\"

set PROJ_FOLD(F320_1)      "$USR_PROJ_PREF\C8051F320_1\\"
set PROJ_FOLD(F326_7)      "$USR_PROJ_PREF\C8051F326_7\\"
set PROJ_FOLD(F34x_64k)    "$USR_PROJ_PREF\C8051F340_2_4_6\\"
set PROJ_FOLD(F34x_32k)    "$USR_PROJ_PREF\C8051F341_3_5_7\\"
set PROJ_FOLD(F38x_64k)    "$USR_PROJ_PREF\C8051F380_1_4_5\\"
set PROJ_FOLD(F38x_32k)    "$USR_PROJ_PREF\C8051F382_3_6_7\\"


set PROJ(F320_1)      "$PROJ_FOLD(F320_1)\USB_App_Firmware_Examples\\F320_1_"
set PROJ(F326_7)      "$PROJ_FOLD(F326_7)\USB_App_Firmware_Examples\\F326_7_"
set PROJ(F34x_64k)    "$PROJ_FOLD(F34x_64k)\USB_App_Firmware_Examples\\F340_2_4_6_"
set PROJ(F34x_32k)    "$PROJ_FOLD(F34x_32k)\USB_App_Firmware_Examples\\F341_3_5_7_"
set PROJ(F38x_64k)    "$PROJ_FOLD(F38x_64k)\USB_App_Firmware_Examples\\F380_1_4_5_"
set PROJ(F38x_32k)    "$PROJ_FOLD(F38x_32k)\USB_App_Firmware_Examples\\F382_3_6_7_"

set NEW_A51_FOLDER          "..\\USB_Bootloader_Firmware_Source\\Auto_gen_BL_HEX\\"
set NEW_A51_FN(F320_1)      "$NEW_A51_FOLDER\\USB_BL_APP_F320_1_16k_STARTUP.A51"
set NEW_A51_FN(F326_7)      "$NEW_A51_FOLDER\\USB_BL_APP_F326_7_16k_STARTUP.A51"
set NEW_A51_FN(F34x_64k)	"$NEW_A51_FOLDER\\USB_BL_APP_F34x_64k_STARTUP.A51"
set NEW_A51_FN(F34x_32k)	"$NEW_A51_FOLDER\\USB_BL_APP_F34x_32k_STARTUP.A51"
set NEW_A51_FN(F38x_64k)	"$NEW_A51_FOLDER\\USB_BL_APP_F38x_64k_STARTUP.A51"
set NEW_A51_FN(F38x_32k)	"$NEW_A51_FOLDER\\USB_BL_APP_F38x_32k_STARTUP.A51"

set AUTO_GEN_STARTUP_A51_END_LINE ";End of custom code for the Application FW Project <-"










proc bl_app_startupA51_update {} {
	global PROJ_FOLD
	global PROJ
	global NEW_A51_FN

	foreach model [array names PROJ_FOLD] {
		puts "current proj $PROJ_FOLD($model)"
		foreach obj_file_name [glob -directory $PROJ_FOLD($model)\USB_App_Firmware_Startup *.A51] {
			bl_tools_update_file $obj_file_name $NEW_A51_FN($model)
		}
	}
}
proc bl_tools_update_file {obj_file_name new_para_file_name} {
	global AUTO_GEN_STARTUP_A51_END_LINE

	set time_stamp [clock format [clock seconds] -format %b_%d_%H_%M_%S]
	# Update the paragraphs in obj_file_name with new_para_file_name
	puts "File name:$obj_file_name"
	puts "Start to processing file ...\n"
	set tmp_file_name $obj_file_name\.tmp

	if {[catch {set obj_file [open $obj_file_name r]} err_msg]} {
		puts "Failed to open object file. Error:$err_msg"
		return;
	}

	if {[catch {set new_para [open $new_para_file_name r]} err_msg]} {
		puts "Failed to open new paragraph file. Error:$err_msg"
		if {$obj_file} {
			close $obj_file
		}
		return;
	}

	if {[catch {set tmp_file [open $tmp_file_name w]}  err_msg]} {
		puts "Failed to crate temp file. Error:$err_msg"
		if {$obj_file} {
			close $obj_file
		}
		if {$new_para} {
			close $new_para
		}
		return;
	}
	gets $new_para line_from_new_para  ;# Ignore first line
	gets $new_para line_from_new_para

	while {[gets $obj_file line] != -1} {
		puts $tmp_file $line
		# Find matched line, start to replace
		if {$line == $line_from_new_para} {
			while {$line != -1 && $line != $AUTO_GEN_STARTUP_A51_END_LINE} {
				gets $new_para line
				puts $tmp_file $line
			}
			break;
		}
	}
	# read out the old paragraphs and drop it
	while {[gets $obj_file line] != -1} {
		if {$line == $AUTO_GEN_STARTUP_A51_END_LINE} {
			break;
		}
	}
	# Read remained lines
	while {[gets $obj_file line] != -1} {
		puts $tmp_file $line
	}

	close $obj_file
	close $tmp_file
	close $new_para

	puts  "\nRename old file ..."
	file rename $obj_file_name  "$obj_file_name\_$time_stamp\.old.tmp"

	puts  "Copy new project file to desternation ..."
	file rename  $tmp_file_name $obj_file_name



	puts "File is updateed."
}



proc bl_app_startupA51_copy_to_example_project { } {
	global PROJ_FOLD
	global PROJ

	foreach model [array names PROJ_FOLD] {
		puts "current proj $PROJ_FOLD($model)"
		foreach src_a51 [glob -directory $PROJ_FOLD($model)\USB_App_Firmware_Startup *.A51] {
			puts "Current MCU model $PROJ_FOLD($model)"
			puts "src A51 file: $src_a51"

			file copy -force $src_a51 "$PROJ($model)\Testpanel1"

			file copy -force $src_a51 "$PROJ($model)\Testpanel2"
		}
	}
}



proc bl_upgrade_user_projects { } {
	global COMP_OPTION
	global COMP_OPTION_LINK
	global PROJ

	puts "project file name:"
	foreach model [array names PROJ] {
		set proj_name  "$PROJ($model)\Testpanel1\\Testpanel1.wsp"
		bl_upgrade_complier_options  $proj_name $COMP_OPTION(ASM)  $COMP_OPTION(C) $COMP_OPTION_LINK($model)
		set proj_name  "$PROJ($model)\Testpanel2\\Testpanel2.wsp"
		bl_upgrade_complier_options  $proj_name $COMP_OPTION(ASM)  $COMP_OPTION(C) $COMP_OPTION_LINK($model)
	}
}



proc bl_upgrade_complier_options { src_file_name asm_option  c_option link_option } {
	set in_file 0
	set tmp_file 0
	set all_file_str ""
	set time_stamp [clock format [clock seconds] -format %b_%d_%H_%M_%S]
	set tmp_wsp_file_name  "tmp_$time_stamp.wsp"


	puts "File name:$src_file_name"
	puts "Start to processing file ...\n"

	if {[catch {set in_file [open $src_file_name r]} err_msg]} {
		puts "Failed to open source file. Error:$err_msg"
		return;
	}

	if {[catch {set tmp_file [open $tmp_wsp_file_name w]}  err_msg]} {
		puts "Failed to crate temp file.Error:$err_msg"
		if {$in_file} {
			close $in_file
		}
		return;
	}

	while {[gets $in_file line] != -1} { ; #Read line until EOF
#		puts "line:$line"
		if {[regexp (AssFlag=) $line]} {
			set line "AssFlag=$asm_option"
			puts "New Asm line:           $line"
		}
		if {[regexp (LinkFlag=) $line]} {
			set line "LinkFlag=$link_option"
			puts "New Linker line:        $line"
		}
		if {[regexp (CompFlag=) $line]} {
			set line "CompFlag=$c_option"
			puts "New Linker line:        $line"
		}
#		lappend all_file_str "$line\n"
		puts $tmp_file $line
	}
	puts  "\nRename old file ..."
	close $in_file
	file rename $src_file_name  "$src_file_name\.$time_stamp\.tmp"

	puts  "Copy new project file to desternation ..."
	close $tmp_file
	file copy  $tmp_wsp_file_name $src_file_name

	puts "All done. Delete temp file"
	file delete $tmp_wsp_file_name
}

