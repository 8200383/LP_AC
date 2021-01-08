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
#include "calendar.h"
#include "employees.h"

#define MAX_FILENAME 256

/**
 * @struct s_details
 * A struct that represents working days per worker
 */
typedef struct
{
	int cod_employee; /**< Reprents the employee code */
	int full_days; /**< Represents the number of full days worked */
	int half_days; /**< Represents the number of half days worked */
	int weekend_days; /**< Represents number of the weekends worked */
	int absent_days; /**< Represents the number of days missed */
	/* TODO: missing processing vars */
} s_details;

/**
 * @struct s_spreadsheet
 * A struct that represents a spreadsheet for a given month
 */
typedef struct
{
	s_details* details; /**< Array of details **/
	e_month month; /**< Represent the month of the spreadsheet **/
	int used; /**< Tracks used capacity of the array **/
	int max_capacity; /**< Tracks max capacity of the array **/
} s_spreadsheet;

// TODO: void h_proc_export_bin(s_spreadsheet* spreadsheet);

/**
 * Allocs an array of structs (s_arr_spreadsheet),
 * containing the month (enum) and details (s_details) for the month
 * @return s_spreadsheet Returns a ptr to a malloced struct of s_spreadsheet returns NULL if failure
 */
s_spreadsheet* h_proc_alloc(int initial_capacity);

/**
 * Opens a binary file in read mode onto a spreadsheet
 * @param filename Path of the file
 * @param month Month to import
 * @return s_spreadsheet Returns a ptr to a malloced struct of s_spreadsheet returns NULL if failure
 */
s_spreadsheet* h_proc_open(const char* filename, e_month month);

/**
 * Loads a spreadsheet into memory by asking a month to import
 * @return s_spreadsheet Returns a ptr to a malloced struct of s_spreadsheet returns NULL if failure
 */
s_spreadsheet* h_proc_import();

/**
 * Add details to an existing month
 * @param spreadsheet Ptr to a spreadsheet
 * @param arr_employees An array of employees
 */
void h_proc_add(s_spreadsheet* spreadsheet, s_arr_employees* arr_employees);

/**
 * Edit details from an existing month
 * @param spreadsheet Ptr to a spreadsheet
 */
void h_proc_edit(s_spreadsheet* spreadsheet);

/**
 * Prints a spreadsheet
 * @param spreadsheet Ptr of spreadsheet
 */
void h_proc_print(s_spreadsheet* spreadsheet);

/**
 * Deletes details in a spreadsheet
 * @param spreadsheet Ptr of spreadsheet
 */
void h_proc_delete(s_spreadsheet* spreadsheet);

/**
 * Free a spreadsheet
 * @param spreadsheet Ptr of spreadsheet
 */
void h_proc_free(s_spreadsheet* spreadsheet);

/**
 * Exports a spreadsheet to CSV
 * @param spreadsheet Ptr of spreadsheet
 */
void h_proc_export_csv(s_spreadsheet* spreadsheet);

/**
 * Generate a filename from a given month and an extension
 * @param month Month to generate
 * @param extension The file extension
 * @return char* Return the generated filename
 */
char* h_proc_generate_filename(e_month month, const char* extension);

/**
 * @return s_error Indicates what went wrong or NULL returned
 */
void h_proc_perform(s_spreadsheet* spreadsheet,
	s_arr_irs* irs_array,
	s_arr_iss* ss_array,
	s_arr_employees* employees_array);

#endif //PROC_H
