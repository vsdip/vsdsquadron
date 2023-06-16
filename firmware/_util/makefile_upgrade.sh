#!/bin/bash

# Path to the source directory
source_dir="../uart_test"

# Path to the destination directories
blink_led_dir="../blink_led"
count_led_dir="../count_led"
relay_test_dir="../relay_test"
delay_test_dir="../delay_test"
line_follower_dir="../line_follower"
servo_test_dir="../servo_test"
sevseg_single_digit_dir="../sevseg_single_digit"
sevseg_four_digit_dir="../sevseg_four_digit"
uart_test_dir="../uart_test"

# Copy the Makefile to blink_led directory
cp "${source_dir}/Makefile" "${blink_led_dir}"

# Copy the Makefile to blink_led directory
cp "${source_dir}/Makefile" "${count_led_dir}"

# Copy the Makefile to relay_test directory
cp "${source_dir}/Makefile" "${relay_test_dir}"

# Copy the Makefile to delay_test directory
cp "${source_dir}/Makefile" "${delay_test_dir}"

# Copy the Makefile to line_follower directory
cp "${source_dir}/Makefile" "${line_follower_dir}"

# Copy the Makefile to servo_test directory
cp "${source_dir}/Makefile" "${servo_test_dir}"

# Copy the Makefile to sevseg_single_digit directory
cp "${source_dir}/Makefile" "${sevseg_single_digit_dir}"

# Copy the Makefile to sevseg_four_digit directory
cp "${source_dir}/Makefile" "${sevseg_four_digit_dir}"

# Copy the Makefile to blink_led directory
cp "${source_dir}/Makefile" "${uart_test_dir}"

echo "Makefile copied successfully."
