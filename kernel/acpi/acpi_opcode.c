/*
 * ZETALOG's Personal COPYRIGHT v2
 *
 * Copyright (c) 2014
 *    ZETALOG - "Lv ZHENG".  All rights reserved.
 *    Author: Lv "Zetalog" Zheng
 *    Internet: zetalog@gmail.com
 *
 * This COPYRIGHT used to protect Personal Intelligence Rights.
 * Redistribution and use in source and binary forms with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the Lv "Zetalog" ZHENG.
 * 2. Permission of reuse of souce code only granted to ZETALOG and the
 *    developer(s) in the companies ZETALOG worked and has redistributed this
 *    software to.  Permission of redistribution of source code only granted
 *    to ZETALOG.
 * 3. Permission of redistribution and/or reuse of binary fully granted
 *    to ZETALOG and the companies ZETALOG worked and has redistributed this
 *    software to.
 * 4. Any modification of this software in the redistributed companies need
 *    not be published to ZETALOG.
 * 5. All source code modifications linked/included this software and modified
 *    by ZETALOG are of ZETALOG's personal COPYRIGHT unless the above COPYRIGHT
 *    is no long disclaimed.
 *
 * THIS SOFTWARE IS PROVIDED BY THE ZETALOG AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE ZETALOG OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @(#)acpi_opcode.c: ACPI opcode information implementation
 * $Id: acpi_opcode.c,v 1.87 2011-10-17 01:40:34 zhenglv Exp $
 */
#include "acpi_int.h"

/*
 * Numbers of opcodes are extracted from LastIndex+1 of
 * acpi_gbl_opcode_info.
 */
#define NUM_PRIMARY_OPCODES		0x53
#define NUM_EXTENDED_OPCODES		0x1D

#define MAX_PRIMARY_OPCODE		0xFF
#define MAX_EXTENDED_OPCODE		0x88
#define NUM_PRIMARY_OPCODE		(MAX_PRIMARY_OPCODE + 1)
#define NUM_EXTENDED_OPCODE		(MAX_EXTENDED_OPCODE + 1)

/* Used for non-assigned opcodes */
#define _UNK				(NUM_PRIMARY_OPCODES + NUM_EXTENDED_OPCODES)

/*
 * Reserved ASCII characters. Do not use any of these for
 * internal opcodes, since they are used to differentiate
 * name strings from AML opcodes
 */
#define _ASC				(_UNK+1)
#define _NAM				(_UNK+2)
#define _PFX				(_UNK+3)

#define NUM_RESERVED_OPCODES		(0x04)

/* Total number of aml opcodes defined */
#define AML_NUM_OPCODES			\
	(NUM_PRIMARY_OPCODES + NUM_EXTENDED_OPCODES + NUM_RESERVED_OPCODES)

struct acpi_opcode_info {
	char *name;
	uint32_t args;
	uint16_t flags;
};

#define ACPI_OP(name, args, flags)		\
	{ (name), (uint32_t)(args), (uint32_t)(flags) }

#define AML_TYPE_WIDTH			5
#define AML_ARG_1(x)			((uint32_t)(x))
#define AML_ARG_2(x)			((uint32_t)(x) << (1 * AML_TYPE_WIDTH))
#define AML_ARG_3(x)			((uint32_t)(x) << (2 * AML_TYPE_WIDTH))
#define AML_ARG_4(x)			((uint32_t)(x) << (3 * AML_TYPE_WIDTH))
#define AML_ARG_5(x)			((uint32_t)(x) << (4 * AML_TYPE_WIDTH))
#define AML_ARG_6(x)			((uint32_t)(x) << (5 * AML_TYPE_WIDTH))

#define AML_ARGS1(a)			(AML_ARG_1(a))
#define AML_ARGS2(a, b)			(AML_ARG_1(a)|AML_ARG_2(b))
#define AML_ARGS3(a, b, c)		(AML_ARG_1(a)|AML_ARG_2(b)|AML_ARG_3(c))
#define AML_ARGS4(a, b, c, d)		(AML_ARG_1(a)|AML_ARG_2(b)|AML_ARG_3(c)|AML_ARG_4(d))
#define AML_ARGS5(a, b, c, d, e)	(AML_ARG_1(a)|AML_ARG_2(b)|AML_ARG_3(c)|AML_ARG_4(d)|AML_ARG_5(e))
#define AML_ARGS6(a, b, c, d, e, f)	(AML_ARG_1(a)|AML_ARG_2(b)|AML_ARG_3(c)|AML_ARG_4(d)|AML_ARG_5(e)|AML_ARG_6(f))

/*
 * All AML opcodes and the parse-time arguments for each. Used by the AML
 * parser  Each list is compressed into a 32-bit number and stored in the
 * master opcode table (in psopcode.c).
 */
#define AML_ACCESSFIELD_ARGS		AML_ARGS1(AML_NAMESTRING)
#define AML_ACQUIRE_ARGS		AML_ARGS2(AML_SUPERNAME, AML_WORDDATA)
#define AML_ADD_ARGS			AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_ALIAS_ARGS			AML_ARGS2(AML_NAMESTRING, AML_NAME)
#define AML_ARG0_ARGS			AML_NONE
#define AML_ARG1_ARGS			AML_NONE
#define AML_ARG2_ARGS			AML_NONE
#define AML_ARG3_ARGS			AML_NONE
#define AML_ARG4_ARGS			AML_NONE
#define AML_ARG5_ARGS			AML_NONE
#define AML_ARG6_ARGS			AML_NONE
#define AML_BANK_FIELD_ARGS		AML_ARGS6(AML_PKGLENGTH, AML_NAMESTRING, AML_NAMESTRING,AML_TERMARG, AML_BYTEDATA, AML_FIELDLIST)
#define AML_BIT_AND_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_BIT_NAND_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_BIT_NOR_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_BIT_NOT_ARGS		AML_ARGS2(AML_TERMARG, AML_TARGET)
#define AML_BIT_OR_ARGS			AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_BIT_XOR_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_BREAK_ARGS			AML_NONE
#define AML_BREAK_POINT_ARGS		AML_NONE
#define AML_BUFFER_ARGS			AML_ARGS3(AML_PKGLENGTH, AML_TERMARG, AML_BYTELIST)
#define AML_BYTE_ARGS			AML_ARGS1(AML_BYTEDATA)
#define AML_BYTELIST_ARGS		AML_ARGS1(AML_NAMESTRING)
#define AML_CONCAT_ARGS			AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_CONCAT_RES_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_COND_REF_OF_ARGS		AML_ARGS2(AML_SUPERNAME, AML_SUPERNAME)
#define AML_CONNECTFIELD_ARGS		AML_ARGS1(AML_NAMESTRING)
#define AML_CONTINUE_ARGS		AML_NONE
#define AML_COPY_ARGS			AML_ARGS2(AML_TERMARG, AML_SIMPLENAME)
#define AML_CREATE_BIT_FIELD_ARGS	AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_NAME)
#define AML_CREATE_BYTE_FIELD_ARGS	AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_NAME)
#define AML_CREATE_DWORD_FIELD_ARGS	AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_NAME)
#define AML_CREATE_FIELD_ARGS		AML_ARGS4(AML_TERMARG, AML_TERMARG, AML_TERMARG, AML_NAME)
#define AML_CREATE_QWORD_FIELD_ARGS	AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_NAME)
#define AML_CREATE_WORD_FIELD_ARGS	AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_NAME)
#define AML_DATA_REGION_ARGS		AML_ARGS4(AML_NAME, AML_TERMARG, AML_TERMARG, AML_TERMARG)
#define AML_DEBUG_ARGS			AML_NONE
#define AML_DECREMENT_ARGS		AML_ARGS1(AML_SUPERNAME)
#define AML_DEREF_OF_ARGS		AML_ARGS1(AML_TERMARG)
#define AML_DEVICE_ARGS			AML_ARGS3(AML_PKGLENGTH, AML_NAME, AML_OBJLIST)
#define AML_DIVIDE_ARGS			AML_ARGS4(AML_TERMARG, AML_TERMARG, AML_TARGET, AML_TARGET)
#define AML_DWORD_ARGS			AML_ARGS1(AML_DWORDDATA)
#define AML_ELSE_ARGS			AML_ARGS2(AML_PKGLENGTH, AML_TERMLIST)
#define AML_EVENT_ARGS			AML_ARGS1(AML_NAME)
#define AML_FATAL_ARGS			AML_ARGS3(AML_BYTEDATA, AML_DWORDDATA, AML_TERMARG)
#define AML_FIELD_ARGS			AML_ARGS4(AML_PKGLENGTH, AML_NAMESTRING, AML_BYTEDATA, AML_FIELDLIST)
#define AML_FIND_SET_LEFT_BIT_ARGS	AML_ARGS2(AML_TERMARG, AML_TARGET)
#define AML_FIND_SET_RIGHT_BIT_ARGS	AML_ARGS2(AML_TERMARG, AML_TARGET)
#define AML_FROM_BCD_ARGS		AML_ARGS2(AML_TERMARG, AML_TARGET)
#define AML_IF_ARGS			AML_ARGS3(AML_PKGLENGTH, AML_TERMARG, AML_TERMLIST)
#define AML_INCREMENT_ARGS		AML_ARGS1(AML_SUPERNAME)
#define AML_INDEX_FIELD_ARGS		AML_ARGS5(AML_PKGLENGTH, AML_NAMESTRING, AML_NAMESTRING, AML_BYTEDATA, AML_FIELDLIST)
#define AML_INDEX_ARGS			AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_LAND_ARGS			AML_ARGS2(AML_TERMARG, AML_TERMARG)
#define AML_LEQUAL_ARGS			AML_ARGS2(AML_TERMARG, AML_TERMARG)
#define AML_LGREATER_ARGS		AML_ARGS2(AML_TERMARG, AML_TERMARG)
#define AML_LGREATEREQUAL_ARGS		AML_ARGS2(AML_TERMARG, AML_TERMARG)
#define AML_LLESS_ARGS			AML_ARGS2(AML_TERMARG, AML_TERMARG)
#define AML_LLESSEQUAL_ARGS		AML_ARGS2(AML_TERMARG, AML_TERMARG)
#define AML_LNOT_ARGS			AML_ARGS1(AML_TERMARG)
#define AML_LNOTEQUAL_ARGS		AML_ARGS2(AML_TERMARG, AML_TERMARG)
#define AML_LOAD_ARGS			AML_ARGS2(AML_NAMESTRING, AML_SUPERNAME)
#define AML_LOAD_TABLE_ARGS		AML_ARGS6(AML_TERMARG, AML_TERMARG, AML_TERMARG, AML_TERMARG, AML_TERMARG, AML_TERMARG)
#define AML_LOCAL0_ARGS			AML_NONE
#define AML_LOCAL1_ARGS			AML_NONE
#define AML_LOCAL2_ARGS			AML_NONE
#define AML_LOCAL3_ARGS			AML_NONE
#define AML_LOCAL4_ARGS			AML_NONE
#define AML_LOCAL5_ARGS			AML_NONE
#define AML_LOCAL6_ARGS			AML_NONE
#define AML_LOCAL7_ARGS			AML_NONE
#define AML_LOR_ARGS			AML_ARGS2(AML_TERMARG, AML_TERMARG)
#define AML_MATCH_ARGS			AML_ARGS6(AML_TERMARG, AML_BYTEDATA, AML_TERMARG, AML_BYTEDATA, AML_TERMARG, AML_TERMARG)
#define AML_METHOD_ARGS			AML_ARGS4(AML_PKGLENGTH, AML_NAME, AML_BYTEDATA, AML_TERMLIST)
#define AML_METHODCALL_ARGS		AML_ARGS1(AML_NAMESTRING)
#define AML_MID_ARGS			AML_ARGS4(AML_TERMARG, AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_MOD_ARGS			AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_MULTIPLY_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_MUTEX_ARGS			AML_ARGS2(AML_NAME, AML_BYTEDATA)
#define AML_NAME_ARGS			AML_ARGS2(AML_NAME, AML_DATAOBJ)
#define AML_NAMEDFIELD_ARGS		AML_ARGS1(AML_NAMESTRING)
#define AML_NAMEPATH_ARGS		AML_ARGS1(AML_NAMESTRING)
#define AML_NOOP_ARGS			AML_NONE
#define AML_NOTIFY_ARGS			AML_ARGS2(AML_SUPERNAME, AML_TERMARG)
#define AML_ONE_ARGS			AML_NONE
#define AML_ONES_ARGS			AML_NONE
#define AML_PACKAGE_ARGS		AML_ARGS3(AML_PKGLENGTH, AML_BYTEDATA, AML_DATAOBJLIST)
#define AML_POWER_RES_ARGS		AML_ARGS5(AML_PKGLENGTH, AML_NAME, AML_BYTEDATA, AML_WORDDATA, AML_OBJLIST)
#define AML_PROCESSOR_ARGS		AML_ARGS6(AML_PKGLENGTH, AML_NAME, AML_BYTEDATA, AML_DWORDDATA, AML_BYTEDATA, AML_OBJLIST)
#define AML_QWORD_ARGS			AML_ARGS1(AML_QWORDDATA)
#define AML_REF_OF_ARGS			AML_ARGS1(AML_SUPERNAME)
#define AML_REGION_ARGS			AML_ARGS4(AML_NAME, AML_BYTEDATA, AML_TERMARG, AML_TERMARG)
#define AML_RELEASE_ARGS		AML_ARGS1(AML_SUPERNAME)
#define AML_RESERVEDFIELD_ARGS		AML_ARGS1(AML_NAMESTRING)
#define AML_RESET_ARGS			AML_ARGS1(AML_SUPERNAME)
#define AML_RETURN_ARGS			AML_ARGS1(AML_TERMARG)
#define AML_REVISION_ARGS		AML_NONE
#define AML_SCOPE_ARGS			AML_ARGS3(AML_PKGLENGTH, AML_NAME, AML_TERMLIST)
#define AML_SERIALFIELD_ARGS		AML_ARGS1(AML_NAMESTRING)
#define AML_SHIFT_LEFT_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_SHIFT_RIGHT_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_SIGNAL_ARGS			AML_ARGS1(AML_SUPERNAME)
#define AML_SIZE_OF_ARGS		AML_ARGS1(AML_SUPERNAME)
#define AML_SLEEP_ARGS			AML_ARGS1(AML_TERMARG)
#define AML_STALL_ARGS			AML_ARGS1(AML_TERMARG)
#define AML_STATICSTRING_ARGS		AML_ARGS1(AML_NAMESTRING)
#define AML_STORE_ARGS			AML_ARGS2(AML_TERMARG, AML_SUPERNAME)
#define AML_STRING_ARGS			AML_ARGS1(AML_CHARLIST)
#define AML_SUBTRACT_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_THERMAL_ZONE_ARGS		AML_ARGS3(AML_PKGLENGTH, AML_NAME, AML_OBJLIST)
#define AML_TIMER_ARGS			AML_NONE
#define AML_TO_BCD_ARGS			AML_ARGS2(AML_TERMARG, AML_TARGET)
#define AML_TO_BUFFER_ARGS		AML_ARGS2(AML_TERMARG, AML_TARGET)
#define AML_TO_DEC_STR_ARGS		AML_ARGS2(AML_TERMARG, AML_TARGET)
#define AML_TO_HEX_STR_ARGS		AML_ARGS2(AML_TERMARG, AML_TARGET)
#define AML_TO_INTEGER_ARGS		AML_ARGS2(AML_TERMARG, AML_TARGET)
#define AML_TO_STRING_ARGS		AML_ARGS3(AML_TERMARG, AML_TERMARG, AML_TARGET)
#define AML_TYPE_ARGS			AML_ARGS1(AML_SUPERNAME)
#define AML_UNLOAD_ARGS			AML_ARGS1(AML_SUPERNAME)
#define AML_VAR_PACKAGE_ARGS		AML_ARGS3(AML_PKGLENGTH, AML_TERMARG, AML_DATAOBJLIST)
#define AML_WAIT_ARGS			AML_ARGS2(AML_SUPERNAME, AML_TERMARG)
#define AML_WHILE_ARGS			AML_ARGS3(AML_PKGLENGTH, AML_TERMARG, AML_TERMLIST)
#define AML_WORD_ARGS			AML_ARGS1(AML_WORDDATA)
#define AML_ZERO_ARGS			AML_NONE

/*
 * Master Opcode information table. A summary of everything we know about each
 * opcode, all in one place.
 */
const struct acpi_opcode_info acpi_gbl_opcode_info[AML_NUM_OPCODES] =
{
/* Index          Name                     Interpreter Args             Flags */
/* ACPI 1.0 opcodes */
/* 00 */ ACPI_OP("Zero",                   AML_ZERO_ARGS,               AML_CONSTANT),
/* 01 */ ACPI_OP("One",                    AML_ONE_ARGS,                AML_CONSTANT),
/* 02 */ ACPI_OP("Alias",                  AML_ALIAS_ARGS,              AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED),
/* 03 */ ACPI_OP("Name",                   AML_NAME_ARGS,               AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED),
/* 04 */ ACPI_OP("ByteConst",              AML_BYTE_ARGS,               AML_CONSTANT),
/* 05 */ ACPI_OP("WordConst",              AML_WORD_ARGS,               AML_CONSTANT),
/* 06 */ ACPI_OP("DwordConst",             AML_DWORD_ARGS,              AML_CONSTANT),
/* 07 */ ACPI_OP("String",                 AML_STRING_ARGS,             AML_CONSTANT),
/* 08 */ ACPI_OP("Scope",                  AML_SCOPE_ARGS,              AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED),
/* 09 */ ACPI_OP("Buffer",                 AML_BUFFER_ARGS,             AML_HAS_ARGS | AML_DEFER | AML_CONSTANT),
/* 0A */ ACPI_OP("Package",                AML_PACKAGE_ARGS,            AML_HAS_ARGS | AML_DEFER | AML_CONSTANT),
/* 0B */ ACPI_OP("Method",                 AML_METHOD_ARGS,             AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED | AML_DEFER),
/* 0C */ ACPI_OP("Local0",                 AML_LOCAL0_ARGS,             0),
/* 0D */ ACPI_OP("Local1",                 AML_LOCAL1_ARGS,             0),
/* 0E */ ACPI_OP("Local2",                 AML_LOCAL2_ARGS,             0),
/* 0F */ ACPI_OP("Local3",                 AML_LOCAL3_ARGS,             0),
/* 10 */ ACPI_OP("Local4",                 AML_LOCAL4_ARGS,             0),
/* 11 */ ACPI_OP("Local5",                 AML_LOCAL5_ARGS,             0),
/* 12 */ ACPI_OP("Local6",                 AML_LOCAL6_ARGS,             0),
/* 13 */ ACPI_OP("Local7",                 AML_LOCAL7_ARGS,             0),
/* 14 */ ACPI_OP("Arg0",                   AML_ARG0_ARGS,               0),
/* 15 */ ACPI_OP("Arg1",                   AML_ARG1_ARGS,               0),
/* 16 */ ACPI_OP("Arg2",                   AML_ARG2_ARGS,               0),
/* 17 */ ACPI_OP("Arg3",                   AML_ARG3_ARGS,               0),
/* 18 */ ACPI_OP("Arg4",                   AML_ARG4_ARGS,               0),
/* 19 */ ACPI_OP("Arg5",                   AML_ARG5_ARGS,               0),
/* 1A */ ACPI_OP("Arg6",                   AML_ARG6_ARGS,               0),
/* 1B */ ACPI_OP("Store",                  AML_STORE_ARGS,              AML_FLAGS_EXEC_1A_1T_1R),
/* 1C */ ACPI_OP("RefOf",                  AML_REF_OF_ARGS,             AML_FLAGS_EXEC_1A_0T_1R),
/* 1D */ ACPI_OP("Add",                    AML_ADD_ARGS,                AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 1E */ ACPI_OP("Concatenate",            AML_CONCAT_ARGS,             AML_FLAGS_EXEC_2A_1T_1R | AML_CONSTANT),
/* 1F */ ACPI_OP("Subtract",               AML_SUBTRACT_ARGS,           AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 20 */ ACPI_OP("Increment",              AML_INCREMENT_ARGS,          AML_FLAGS_EXEC_1A_0T_1R | AML_CONSTANT),
/* 21 */ ACPI_OP("Decrement",              AML_DECREMENT_ARGS,          AML_FLAGS_EXEC_1A_0T_1R | AML_CONSTANT),
/* 22 */ ACPI_OP("Multiply",               AML_MULTIPLY_ARGS,           AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 23 */ ACPI_OP("Divide",                 AML_DIVIDE_ARGS,             AML_FLAGS_EXEC_2A_2T_1R | AML_CONSTANT),
/* 24 */ ACPI_OP("ShiftLeft",              AML_SHIFT_LEFT_ARGS,         AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 25 */ ACPI_OP("ShiftRight",             AML_SHIFT_RIGHT_ARGS,        AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 26 */ ACPI_OP("And",                    AML_BIT_AND_ARGS,            AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 27 */ ACPI_OP("NAnd",                   AML_BIT_NAND_ARGS,           AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 28 */ ACPI_OP("Or",                     AML_BIT_OR_ARGS,             AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 29 */ ACPI_OP("NOr",                    AML_BIT_NOR_ARGS,            AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 2A */ ACPI_OP("XOr",                    AML_BIT_XOR_ARGS,            AML_FLAGS_EXEC_2A_1T_1R | AML_MATH | AML_CONSTANT),
/* 2B */ ACPI_OP("Not",                    AML_BIT_NOT_ARGS,            AML_FLAGS_EXEC_1A_1T_1R | AML_CONSTANT),
/* 2C */ ACPI_OP("FindSetLeftBit",         AML_FIND_SET_LEFT_BIT_ARGS,  AML_FLAGS_EXEC_1A_1T_1R | AML_CONSTANT),
/* 2D */ ACPI_OP("FindSetRightBit",        AML_FIND_SET_RIGHT_BIT_ARGS, AML_FLAGS_EXEC_1A_1T_1R | AML_CONSTANT),
/* 2E */ ACPI_OP("DerefOf",                AML_DEREF_OF_ARGS,           AML_FLAGS_EXEC_1A_0T_1R),
/* 2F */ ACPI_OP("Notify",                 AML_NOTIFY_ARGS,             AML_FLAGS_EXEC_2A_0T_0R),
/* 30 */ ACPI_OP("SizeOf",                 AML_SIZE_OF_ARGS,            AML_FLAGS_EXEC_1A_0T_1R | AML_NO_OPERAND_RESOLVE),
/* 31 */ ACPI_OP("Index",                  AML_INDEX_ARGS,              AML_FLAGS_EXEC_2A_1T_1R),
/* 32 */ ACPI_OP("Match",                  AML_MATCH_ARGS,              AML_FLAGS_EXEC_6A_0T_1R | AML_CONSTANT),
/* 33 */ ACPI_OP("CreateDWordField",       AML_CREATE_DWORD_FIELD_ARGS, AML_HAS_ARGS | AML_NSOBJECT | AML_NSNODE | AML_DEFER | AML_CREATE),
/* 34 */ ACPI_OP("CreateWordField",        AML_CREATE_WORD_FIELD_ARGS,  AML_HAS_ARGS | AML_NSOBJECT | AML_NSNODE | AML_DEFER | AML_CREATE),
/* 35 */ ACPI_OP("CreateByteField",        AML_CREATE_BYTE_FIELD_ARGS,  AML_HAS_ARGS | AML_NSOBJECT | AML_NSNODE | AML_DEFER | AML_CREATE),
/* 36 */ ACPI_OP("CreateBitField",         AML_CREATE_BIT_FIELD_ARGS,   AML_HAS_ARGS | AML_NSOBJECT | AML_NSNODE | AML_DEFER | AML_CREATE),
/* 37 */ ACPI_OP("ObjectType",             AML_TYPE_ARGS,               AML_FLAGS_EXEC_1A_0T_1R | AML_NO_OPERAND_RESOLVE),
/* 38 */ ACPI_OP("LAnd",                   AML_LAND_ARGS,               AML_FLAGS_EXEC_2A_0T_1R | AML_LOGICAL_NUMERIC | AML_CONSTANT),
/* 39 */ ACPI_OP("LOr",                    AML_LOR_ARGS,                AML_FLAGS_EXEC_2A_0T_1R | AML_LOGICAL_NUMERIC | AML_CONSTANT),
/* 3A */ ACPI_OP("LNot",                   AML_LNOT_ARGS,               AML_FLAGS_EXEC_1A_0T_1R | AML_CONSTANT),
/* 3B */ ACPI_OP("LEqual",                 AML_LEQUAL_ARGS,             AML_FLAGS_EXEC_2A_0T_1R | AML_LOGICAL | AML_CONSTANT),
/* 3C */ ACPI_OP("LGreater",               AML_LGREATER_ARGS,           AML_FLAGS_EXEC_2A_0T_1R | AML_LOGICAL | AML_CONSTANT),
/* 3D */ ACPI_OP("LLess",                  AML_LLESS_ARGS,              AML_FLAGS_EXEC_2A_0T_1R | AML_LOGICAL | AML_CONSTANT),
/* 3E */ ACPI_OP("If",                     AML_IF_ARGS,                 AML_HAS_ARGS),
/* 3F */ ACPI_OP("Else",                   AML_ELSE_ARGS,               AML_HAS_ARGS),
/* 40 */ ACPI_OP("While",                  AML_WHILE_ARGS,              AML_HAS_ARGS),
/* 41 */ ACPI_OP("Noop",                   AML_NOOP_ARGS,               0),
/* 42 */ ACPI_OP("Return",                 AML_RETURN_ARGS,             AML_HAS_ARGS),
/* 43 */ ACPI_OP("Break",                  AML_BREAK_ARGS,              0),
/* 44 */ ACPI_OP("BreakPoint",             AML_BREAK_POINT_ARGS,        0),
/* 45 */ ACPI_OP("Ones",                   AML_ONES_ARGS,               AML_CONSTANT),
/* ACPI 2.0 opcodes */
/* 46 */ ACPI_OP("QwordConst",             AML_QWORD_ARGS,              AML_CONSTANT),
/* 47 */ ACPI_OP("Package", /* Var */      AML_VAR_PACKAGE_ARGS,        AML_HAS_ARGS | AML_DEFER),
/* 48 */ ACPI_OP("ConcatenateResTemplate", AML_CONCAT_RES_ARGS,         AML_FLAGS_EXEC_2A_1T_1R | AML_CONSTANT),
/* 49 */ ACPI_OP("Mod",                    AML_MOD_ARGS,                AML_FLAGS_EXEC_2A_1T_1R | AML_CONSTANT),
/* 4A */ ACPI_OP("CreateQWordField",       AML_CREATE_QWORD_FIELD_ARGS, AML_HAS_ARGS | AML_NSOBJECT | AML_NSNODE | AML_DEFER | AML_CREATE),
/* 4B */ ACPI_OP("ToBuffer",               AML_TO_BUFFER_ARGS,          AML_FLAGS_EXEC_1A_1T_1R | AML_CONSTANT),
/* 4C */ ACPI_OP("ToDecimalString",        AML_TO_DEC_STR_ARGS,         AML_FLAGS_EXEC_1A_1T_1R | AML_CONSTANT),
/* 4D */ ACPI_OP("ToHexString",            AML_TO_HEX_STR_ARGS,         AML_FLAGS_EXEC_1A_1T_1R | AML_CONSTANT),
/* 4E */ ACPI_OP("ToInteger",              AML_TO_INTEGER_ARGS,         AML_FLAGS_EXEC_1A_1T_1R | AML_CONSTANT),
/* 4F */ ACPI_OP("ToString",               AML_TO_STRING_ARGS,          AML_FLAGS_EXEC_2A_1T_1R | AML_CONSTANT),
/* 50 */ ACPI_OP("CopyObject",             AML_COPY_ARGS,               AML_FLAGS_EXEC_1A_1T_1R),
/* 51 */ ACPI_OP("Mid",                    AML_MID_ARGS,                AML_FLAGS_EXEC_3A_1T_1R | AML_CONSTANT),
/* 52 */ ACPI_OP("Continue",               AML_CONTINUE_ARGS,           0),

/* Prefixed opcodes (Two-byte opcodes with a prefix op) */
/* ACPI 1.0 opcodes */
/* 00 */ ACPI_OP("Mutex",                  AML_MUTEX_ARGS,              AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED),
/* 01 */ ACPI_OP("Event",                  AML_EVENT_ARGS,              AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED ),
/* 02 */ ACPI_OP("CondRefOf",              AML_COND_REF_OF_ARGS,        AML_FLAGS_EXEC_1A_1T_1R),
/* 03 */ ACPI_OP("CreateField",            AML_CREATE_FIELD_ARGS,       AML_HAS_ARGS | AML_NSOBJECT | AML_NSNODE | AML_DEFER | AML_FIELD | AML_CREATE),
/* 04 */ ACPI_OP("Load",                   AML_LOAD_ARGS,               AML_FLAGS_EXEC_1A_1T_0R),
/* 05 */ ACPI_OP("Stall",                  AML_STALL_ARGS,              AML_FLAGS_EXEC_1A_0T_0R),
/* 06 */ ACPI_OP("Sleep",                  AML_SLEEP_ARGS,              AML_FLAGS_EXEC_1A_0T_0R),
/* 07 */ ACPI_OP("Acquire",                AML_ACQUIRE_ARGS,            AML_FLAGS_EXEC_2A_0T_1R),
/* 08 */ ACPI_OP("Signal",                 AML_SIGNAL_ARGS,             AML_FLAGS_EXEC_1A_0T_0R),
/* 09 */ ACPI_OP("Wait",                   AML_WAIT_ARGS,               AML_FLAGS_EXEC_2A_0T_1R),
/* 0A */ ACPI_OP("Reset",                  AML_RESET_ARGS,              AML_FLAGS_EXEC_1A_0T_0R),
/* 0B */ ACPI_OP("Release",                AML_RELEASE_ARGS,            AML_FLAGS_EXEC_1A_0T_0R),
/* 0C */ ACPI_OP("FromBCD",                AML_FROM_BCD_ARGS,           AML_FLAGS_EXEC_1A_1T_1R | AML_CONSTANT),
/* 0D */ ACPI_OP("ToBCD",                  AML_TO_BCD_ARGS,             AML_FLAGS_EXEC_1A_1T_1R | AML_CONSTANT),
/* 0E */ ACPI_OP("Unload",                 AML_UNLOAD_ARGS,             AML_FLAGS_EXEC_1A_0T_0R),
/* 0F */ ACPI_OP("Revision",               AML_REVISION_ARGS,           0),
/* 10 */ ACPI_OP("Debug",                  AML_DEBUG_ARGS,              0),
/* 11 */ ACPI_OP("Fatal",                  AML_FATAL_ARGS,              AML_FLAGS_EXEC_3A_0T_0R),
/* 12 */ ACPI_OP("OperationRegion",        AML_REGION_ARGS,             AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED | AML_DEFER),
/* 13 */ ACPI_OP("Field",                  AML_FIELD_ARGS,              AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_FIELD),
/* 14 */ ACPI_OP("Device",                 AML_DEVICE_ARGS,             AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED),
/* 15 */ ACPI_OP("Processor",              AML_PROCESSOR_ARGS,          AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED),
/* 16 */ ACPI_OP("PowerResource",          AML_POWER_RES_ARGS,          AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED),
/* 17 */ ACPI_OP("ThermalZone",            AML_THERMAL_ZONE_ARGS,       AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED),
/* 18 */ ACPI_OP("IndexField",             AML_INDEX_FIELD_ARGS,        AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_FIELD),
/* 19 */ ACPI_OP("BankField",              AML_BANK_FIELD_ARGS,         AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_FIELD | AML_DEFER),
/* ACPI 2.0 opcodes */
/* 1A */ ACPI_OP("LoadTable",              AML_LOAD_TABLE_ARGS,         AML_FLAGS_EXEC_6A_0T_1R),
/* 1B */ ACPI_OP("DataTableRegion",        AML_DATA_REGION_ARGS,        AML_HAS_ARGS | AML_NSOBJECT | AML_NSOPCODE | AML_NSNODE | AML_NAMED | AML_DEFER),
/* ACPI 3.0 opcodes */
/* 1C */ ACPI_OP("Timer",                  AML_TIMER_ARGS,              AML_FLAGS_EXEC_0A_0T_1R),
};

/*
 * This table is directly indexed by the opcodes It returns
 * an index into the opcode table (acpi_gbl_opcode_info)
 */
const uint8_t acpi_gbl_short_opcode_indexes[256] =
{
/*              0     1     2     3     4     5     6     7  */
/*              8     9     A     B     C     D     E     F  */
/* 0x00 */    0x00, 0x01, _UNK, _UNK, _UNK, _UNK, 0x02, _UNK,
/* 0x08 */    0x03, _UNK, 0x04, 0x05, 0x06, 0x07, 0x46, _UNK,
/* 0x10 */    0x08, 0x09, 0x0a, 0x47, 0x0b, _UNK, _UNK, _UNK,
/* 0x18 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x20 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x28 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _PFX, _PFX,
/* 0x30 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, 0x7D,
/* 0x38 */    0x7F, 0x80, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x40 */    _UNK, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC,
/* 0x48 */    _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC,
/* 0x50 */    _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC,
/* 0x58 */    _ASC, _ASC, _ASC, _UNK, _PFX, _UNK, _PFX, _ASC,
/* 0x60 */    0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13,
/* 0x68 */    0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, _UNK,
/* 0x70 */    0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22,
/* 0x78 */    0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a,
/* 0x80 */    0x2b, 0x2c, 0x2d, 0x2e, 0x48, 0x49, 0x2f, 0x30,
/* 0x88 */    0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x4A,
/* 0x90 */    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x4B, 0x4C,
/* 0x98 */    0x4D, 0x4E, _UNK, _UNK, 0x4F, 0x50, 0x51, 0x52,
/* 0xA0 */    0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, _UNK, _UNK,
/* 0xA8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xB0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xB8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xC0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xC8 */    _UNK, _UNK, _UNK, _UNK, 0x44, _UNK, _UNK, _UNK,
/* 0xD0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xD8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xE0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xE8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xF0 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xF8 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, 0x45,
};

/*
 * This table is indexed by the second opcode of the extended opcode
 * pair. It returns an index into the opcode table (acpi_gbl_opcode_info)
 */
const uint8_t acpi_gbl_long_opcode_indexes[NUM_EXTENDED_OPCODE] =
{
/*              0     1     2     3     4     5     6     7  */
/*              8     9     A     B     C     D     E     F  */
/* 0x00 */    _UNK, 0x00, 0x01, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x08 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x10 */    _UNK, _UNK, 0x02, 0x03, _UNK, _UNK, _UNK, _UNK,
/* 0x18 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, 0x1A,
/* 0x20 */    0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
/* 0x28 */    0x0C, 0x0D, 0x0E, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x30 */    0x0F, 0x10, 0x11, 0x1C, _UNK, _UNK, _UNK, _UNK,
/* 0x38 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x40 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x48 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x50 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x58 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x60 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x68 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x70 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x78 */    _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x80 */    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
/* 0x88 */    0x1B,
};

const struct acpi_opcode_info *acpi_opcode_get_info(uint16_t opcode)
{
	int16_t op_index = -1;

	/*
	 * Detect normal 8-bit opcode or extended 16-bit opcode
	 */
	if (!(opcode & 0xFF00))
		op_index = acpi_gbl_short_opcode_indexes[(uint8_t)opcode];
	if ((opcode & 0xFF00) == AML_EXTENDED_OPCODE &&
	    (opcode & 0xFF00) <= MAX_EXTENDED_OPCODE)
		op_index = acpi_gbl_long_opcode_indexes[(uint8_t)opcode] +
			   NUM_PRIMARY_OPCODES;

	if (op_index > 0)
		return (&acpi_gbl_opcode_info[op_index]);

	/* Unknown AML opcode */
	acpi_warn("Unknown AML opcode [%4.4X]\n", opcode);
	return &acpi_gbl_opcode_info[_UNK];
}

union acpi_opcode *acpi_opcode_alloc(uint16_t opcode)
{
	union acpi_opcode *op;
	const struct acpi_opcode_info *op_info;
	uint8_t flags = ACPI_OPCODE_GENERIC;
	
	op_info = acpi_opcode_get_info(opcode);
	
	if (op_info->flags & AML_DEFER)
		flags = ACPI_OPCODE_DEFERRED;
	else if (op_info->flags & AML_NAMED)
		flags = ACPI_OPCODE_NAMED;
	
	/* Allocate the minimum required size object */
	if (flags == ACPI_OPCODE_GENERIC)
		op = acpi_os_allocate_zeroed(sizeof (struct acpi_opcode_common));
	else
		op = acpi_os_allocate_zeroed(sizeof (struct acpi_opcode_named));
	if (op) {
		op->common.descriptor_type = ACPI_DESC_TYPE_OPCODE;
		op->common.aml_opcode = opcode;
		op->common.flags = flags;
	}
	
	return op;
}

void acpi_opcode_free(union acpi_opcode *op)
{
	acpi_os_free(op);
}
