/*****************************************************************************

Copyright (c) 2016, MariaDB Corporation.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Suite 500, Boston, MA 02110-1335 USA

*****************************************************************************/

/**************************************************//**
@file include/dict0tableoptions.h
Definitions for the system table SYS_TABLE_OPTIONS

Created 22/01/2006 Jan Lindström
*******************************************************/

#ifndef dict0tableoptions_h
#define dict0tableoptions_h

#include "univ.i"

/** Data structure to hold contents of SYS_TABLE_OPTIONS */
struct dict_tableoptions_t{
	table_id_t		table_id;
	/* true if table page compressed */
	bool			page_compressed;
	/* Used compression level if set */
	ulonglong		page_compression_level;
	/* dict0types.h: ATOMIC_WRITES_DEFAULT, _ON, or _OFF */
	atomic_writes_t		atomic_writes;
	/* fil0crypt.h: FIL_SPACE_ENCRYPTION_DEFAULT, _ON, or _OFF */
	fil_encryption_t	encryption;
	/* Used encryption key identifier if set */
	ulonglong		encryption_key_id;
	/* true if table options need to be stored */
	bool			need_stored;
};

/********************************************************************//**
This function parses a SYS_TABLE_OPTIONS record, extracts necessary
information from the record and returns it to the caller.
@return error message or NULL if successfull */
UNIV_INTERN
const char*
dict_process_sys_tableoptions(
/*==========================*/
	mem_heap_t*	heap,		/*!< in/out: heap memory */
	const rec_t*	rec,		/*!< in: current SYS_TABLE_OPTIONS rec */
	dict_tableoptions_t* table_options); /*!< out: table options */

/********************************************************************//**
Gets the table options from SYS_TABLE_OPTIONS based on table_id
@return true if found, false if not found */
UNIV_INTERN
bool
dict_get_table_options(
/*===================*/
	table_id_t		table_id,	/*!< in: table id */
	dict_tableoptions_t*	options,	/*!< out:table options */
	bool			fixed);		/*!< in: can we fix the
						dictionary ? */

/********************************************************************//**
Gets the table options from SYS_TABLE_OPTIONS
@return true if found, false if not found */
UNIV_INTERN
bool
dict_get_table_options(
/*===================*/
	dict_table_t*	table,	/*!< in/out: table */
	bool		fixed);	/*!< in: can we fix the
				dictionary ? */

/********************************************************************//**
Update the record in SYS_TABLE_OPTIONS.
@return	DB_SUCCESS if OK, dberr_t if the update failed */
UNIV_INTERN
dberr_t
dict_update_tableoptions(
/*=====================*/
	const dict_table_t* table);	/*!< in: table object */

/********************************************************************//**
Insert record into SYS_TABLE_OPTIONS
@return	DB_SUCCESS if OK, dberr_t if the insert failed */
UNIV_INTERN
dberr_t
dict_insert_tableoptions(
/*=====================*/
	const dict_table_t*	table,	/*!< in: table object */
	bool			fixed);	/*!< in: can we fix the
					dictionary ? */

/********************************************************************//**
Update the table flags in SYS_TABLES.
@return	DB_SUCCESS if OK, dberr_t if the update failed */
UNIV_INTERN
dberr_t
dict_update_table_flags(
/*=====================*/
	const dict_table_t*	table,	/*!< in: table object */
	bool			fixed);	/*!< in: can we fix the
					dictionary ? */

/********************************************************************//**
Delete the record in SYS_TABLE_OPTIONS.
@return	DB_SUCCESS if OK, dberr_t if the update failed */
UNIV_INTERN
dberr_t
dict_delete_tableoptions(
/*=====================*/
	const dict_table_t*	table,	/*!< in: table object */
	trx_t*			trx,	/*!< in: trx */
	bool			fixed);	/*!< in: can we fix the
					dictionary ? */

#endif /* dict0tableoptions_h */

