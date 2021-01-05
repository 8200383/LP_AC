/**
 * @file proc.h
 * @author Micael Dias, Hugo Carvalho
 * @date 26/12/20
 * @brief Salary Processing
 */

#ifndef PROC_H
#define PROC_H

#include "irs.h"
#include "iss.h"
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
	/* TODO: missing processing vars */
} s_spreadsheet;

typedef struct {
	s_spreadsheet* spreadsheets;
	int used;
	int max_capacity;
} s_arr_spreadsheets;

s_arr_spreadsheets* h_proc_alloc(int initial_capacity);
s_arr_spreadsheets* h_proc_open(const char* filename);
void h_proc_scan_fields(s_spreadsheet* spreadsheet, e_month month);
void h_proc_edit(s_arr_spreadsheets* array, e_month month);
void h_proc_add(s_arr_spreadsheets* array, e_month month);
void h_proc_print(s_arr_spreadsheets* array);
void h_proc_delete(s_arr_spreadsheets* array);
void h_proc_free(s_arr_spreadsheets* array);

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

/**
 * TODO: s_error* h_proc_perform(s_arr_employee* empl_arr, s_arr_irs* irs_arr, s_arr_seg_social* segs_arr, s_arr_spreadsheet* ss_arr, e_month month);
 * NOTA:
 * A informação referente ao processamento do salário deverá ficar armazenada
 * em memória/disco e adicionalmente guardada como relatório o num  ficheiro de texto (ex: CSV)
 * Após processamento: call h_proc_export_bin(), h_proc_export_csv() em h_menu_processing() [perguntar sempre]
 *
 * @param empl_arr Array of Employees
 * @param irs_arr Array of IRS
 * @param segs_arr Array of Social Secutiry
 * @param ss_arr Array of Spreadshhets
 * @param month The month to process, if NULL process all months
 * @return s_error Indicates what went wrong or NULL returned
 */

#endif //PROC_H
