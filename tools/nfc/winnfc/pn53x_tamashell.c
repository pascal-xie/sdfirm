/*-
 * Public platform independent Near Field Communication (NFC) library examples
 * 
 * Copyright (C) 2010, Romuald Conty
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  1) Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer. 
 *  2 )Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * Note that this license only applies on the examples, NFC library itself is under LGPL
 *
 */

/* Configures the NFC device to communicate with a SAM (Secure Access Module).  */

#define _GNU_SOURCE /* for getline on system with glibc < 2.10 */
#define _POSIX_C_SOURCE 200809L /* for getline on system with glibc >= 2.10 */

#include <stdio.h>
#ifdef HAVE_READLINE
#  include <readline/readline.h>
#  include <readline/history.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
/* Needed by sleep() under Unix */
#  define SUSP_TIME	1000 /* usecs. */
#else
/* Needed by Sleep() under Windows */
#  include <winbase.h>
#  define sleep Sleep
#  define SUSP_TIME	1 /* msecs. */
#endif


#include <host/nfc.h>

#include "nfc-utils.h"
#include "../libnfc/chips/pn53x.h"

#define MAX_FRAME_LEN 264

int main(int argc, const char* argv[])
{
	nfc_device_t* pnd;
	byte_t abtRx[MAX_FRAME_LEN];
	byte_t abtTx[MAX_FRAME_LEN];
	size_t szRx = sizeof(abtRx);
	size_t szTx;
	char * cmd;
	char * prompt="> ";
	FILE* input = NULL;
	int i;

	if (argc >= 2) {
		if ((input = fopen(argv[1], "r")) == NULL) {
			ERR ("%s", "Cannot open file.");
			return EXIT_FAILURE;
		}
	}
	
	/* Try to open the NFC reader */
	pnd = nfc_connect(NULL);
	
	if (pnd == NULL) {
		ERR("%s", "Unable to connect to NFC device.");
		return EXIT_FAILURE;
	}
	
	printf("Connected to NFC reader: %s\n", pnd->acName);
	nfc_initiator_init(pnd);
	
	while (1) {
		int offset = 0;
#ifdef HAVE_READLINE
		if (input == NULL) {
			/* means we use stdin */
			cmd=readline(prompt);
			/* NULL if ctrl-d */
			if (cmd == NULL) {
				printf("Bye!\n");
				break;
			}
			add_history(cmd);
		} else {
#endif
			size_t n = 255;
			char * ret = NULL;
			cmd = malloc(n);
			printf("%s", prompt);
			fflush(0);
			if (input != NULL) {
				ret = fgets(cmd, n, input);
			} else {
				ret = fgets(cmd, n, stdin);
			}
			if (ret == NULL || strlen(cmd) <= 0) {
				printf("Bye!\n");
				free(cmd);
				break;
			}
			/* FIXME: print only if read from redirected stdin
			 *        (i.e. script)
			 */
			printf("%s", cmd);
#ifdef HAVE_READLINE
		}
#endif
		if (cmd[0] == 'q') {
			printf("Bye!\n");
			free(cmd);
			break;
		}
		if (cmd[0] == 'p') {
			int s = 0;
			offset++;
			while (isspace(cmd[offset])) {
				offset++;
			}
			sscanf(cmd+offset, "%d", &s);
			printf("Pause for %i msecs\n", s);
			if (s>0) {
				sleep(s * SUSP_TIME);
			}
			free(cmd);
			continue;
		}
		szTx = 0;
		for (i = 0; i < MAX_FRAME_LEN-10; i++) {
			int size;
			byte_t byte;
			while (isspace(cmd[offset])) {
				offset++;
			}
			size = sscanf(cmd+offset, "%2x", (unsigned int*)&byte);
			if (size < 1) {
				break;
			}
			abtTx[i] = byte;
			szTx++;
			if (cmd[offset+1] == 0) {
				/* if last hex was only 1 symbol */
				break;
			}
			offset += 2;
		}
		
		if ((int)szTx < 1) {
			free(cmd);
			continue;
		}
		printf("Tx: ");
		print_hex((byte_t*)abtTx,szTx);
		
		szRx = sizeof(abtRx);
		if (!pn53x_transceive (pnd, abtTx, szTx, abtRx, &szRx, NULL)) {
			free(cmd);
			nfc_perror(pnd, "Rx");
			continue;
		}
		
		printf("Rx: ");
		print_hex(abtRx, szRx);
		free(cmd);
	}
	
	if (input != NULL) {
		fclose(input);
	}
	nfc_disconnect(pnd);
	return 1;
}
