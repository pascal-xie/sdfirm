/*-
 * Public platform independent Near Field Communication (NFC) library
 * 
 * Copyright (C) 2011, Romuald Conty, Romain Tartière
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

/* Defines some macros extracted for ISO/IEC 7816-4 */

#ifndef __NFC_ISO7816_H_INCLUDE__
#define __NFC_ISO7816_H_INCLUDE__

#define ISO7816_C_APDU_COMMAND_HEADER_LEN 4
#define ISO7816_SHORT_APDU_MAX_DATA_LEN 256
#define ISO7816_SHORT_C_APDU_MAX_OVERHEAD 2
#define ISO7816_SHORT_R_APDU_RESPONSE_TRAILER_LEN 2

#define ISO7816_SHORT_C_APDU_MAX_LEN (ISO7816_C_APDU_COMMAND_HEADER_LEN + ISO7816_SHORT_APDU_MAX_DATA_LEN + ISO7816_SHORT_C_APDU_MAX_OVERHEAD)
#define ISO7816_SHORT_R_APDU_MAX_LEN (ISO7816_SHORT_APDU_MAX_DATA_LEN + ISO7816_SHORT_R_APDU_RESPONSE_TRAILER_LEN)

#endif /* __NFC_ISO7816_H_INCLUDE__ */
