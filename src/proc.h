/**
 * @file proc.h
 * @author Micael Dias, Hugo Carvalho
 * @date 26/12/20
 * @brief Salary Processing
 */

#ifndef PROC_H
#define PROC_H

#include "irs.h"
#include "seg_social.h"
#include "error.h"
#include "calendar.h"

#define MAX_FILENAME 256

/**
 * @struct s_details
 * A structure that represents working days per worker
 */
typedef struct {
	int full_days; /**< Represents the number of full days worked */
	int half_days; /**< Represents the number of half days worked */
	int weekend_days; /**< Represents number of the weekends worked */
	int absent_days; /**< Represents the number of days missed */
} s_details;

/**
 * @struct s_spreadsheet
 * A structure that represents the details of the workers per month
 */
typedef struct {
	s_details* details; /**< Stores information about each worker */
	e_month month; /**< Identify the month of the spreadsheet */
	char* filename; /**< Indentify the name of the spreadsheet */
} s_spreadsheet;

/**
 * @struct s_arr_spreadsheet
 * A struct to handle many spreadsheets
 */
typedef struct {
	s_spreadsheet* spreadsheets; /**< This stores an array of spreadsheets */
	int used; /**< This keeps tracking of used elements in the array */
	int max_capacity; /**< This keeps tracking of max_capcity in array */
} s_arr_spreadsheet;

/**
 * TODO: s_error* h_proc_alloc();
 * @brief Allocs an array type of s_arr_spreadsheets
 * This functions allocs an array of structs (s_arr_spreadsheet),
 * the variable spreadsheets is set to NULL at first
 * @return s_arr_spreadsheet Returns an array of spreadsheets
 */

/**
 * TODO: s_arr_spreadsheet* h_proc_import_bin(const char* path);
 * Import a spreadsheet and malloc s_arr_spreadsheet as needed
 * @param path The path of the spreadsheet file
 * @return s_arr_spreadsheet Returns an array of spreadsheets, NULL if nothing found
 */

/**
 * TODO: s_error* h_proc_export_bin(s_arr_spreadsheet* arr, const char* path, e_month month);
 * Export all spreadsheets or a single month
 * @param arr The array of spreadsheets
 * @param path The path of the spreadsheet file
 * @param month The month to export, if NULL all months will be exported
 * @return s_error Indicates what went wrong or NULL returned
 */

/**
 * TODO: s_error* h_proc_export_csv(s_arr_spreadsheet* arr, const char* path, e_month month);
 * Export all spreadsheets or a single month to CSV
 * @param arr The array of spreadsheets
 * @param path The path of the spreadsheet file
 * @param month The month to export, if NULL all months will be exported
 * @return s_error Indicates what went wrong or NULL returned
 */

/**
 * TODO: s_error* h_proc_print(s_arr_spreadsheet* arr);
 * Prints worker details by month
 * @param arr An array of spreadsheets
 * @return s_error Indicates what went wrong or NULL returned
 */

/**
 * TODO: s_error* h_proc_add(s_arr_spreadsheet* arr);
 * Add new month or add month details
 * @param arr An array of spreadsheets (must be malloc first)
 * @return s_error Indicates what went wrong or NULL returned
 */

/**
 * TODO: s_error* h_proc_edit(s_arr_spreadsheet* arr);
 * Edit month or edit month details
 * @param arr An array of spreadsheets (must be malloc first)
 * @return s_error Indicates what went wrong or NULL returned
 */

/**
 * TODO: s_error* h_proc_delete(s_arr_spreadsheet* arr)
 * Delete a month or delete month details
 * @param arr An array of spreadsheets (must be malloc first)
 * @return s_error Indicates what went wrong or NULL returned
 */

/**
 * Generate a filename from a given month and an extension
 * @param month give it a month
 * @param extension file extension like .dat, .bin
 * @return char* the generated filename
 */
char* h_proc_generate_filename(e_month month, const char* extension);

//s_arr_spreadsheet* h_proc_perform(s_arr_irs irs_array, s_arr_seg_social ss_array);

#endif //PROC_H
