/* Copyright 2012 Konstantin Nikiforov <helllamer@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Description: NIF-adapter for levenshtein.c */

#include "erl_nif.h"
#include <stdio.h>
#include <string.h>

extern int levenshtein_distance(char *s, char*t);;

char * get_str_from_binary(ErlNifEnv* env, const ERL_NIF_TERM argv_b);
char * get_str_from_list(ErlNifEnv* env, const ERL_NIF_TERM argv_b);
char * get_str_from_term(ErlNifEnv* env, const ERL_NIF_TERM argv);

// Distance calculation.
// $1, $2 = binary() | string()
static ERL_NIF_TERM levenshtein_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
        int ret;
	char *s0, *s1;	
	
	s0 = get_str_from_term(env, argv[0]);
	s1 = get_str_from_term(env, argv[1]);
	
	ret = levenshtein_distance(s0, s1);

	enif_free(s0);
	enif_free(s1);
	return enif_make_int(env, ret);
	//return enif_make_badarg(env);
}

// depending on argument type (binary or list) call subfunctions
char * get_str_from_term(ErlNifEnv* env, const ERL_NIF_TERM argv) {
    char * s;
    if (enif_is_binary(env, argv)) {
	s = get_str_from_binary(env, argv);
    } else {
	if (enif_is_list(env, argv)) {
	    s = get_str_from_list(env, argv);
	}
    }
    return s;
}

// Get string from binary.
// FIXME Currently, memcpy is used to extract strings because no \0 in the end.
//	 But copying full string just to add a symbol to it is really bad idea.
//	 It will be good to avoid using any memory copy.
char * get_str_from_binary(ErlNifEnv* env, const ERL_NIF_TERM argv_b) {
    ErlNifBinary bin;
    enif_inspect_binary(env, argv_b, &bin);

    char *s = enif_alloc(bin.size + 1);
    strncpy(s, bin.data, bin.size);
    *(s + bin.size) = '\0';

    return s;
}

// Get string from list. 
char * get_str_from_list(ErlNifEnv* env, const ERL_NIF_TERM argv_l) {
    unsigned int len;
    enif_get_list_length(env, argv_l, &len);
    char * s = enif_alloc(len + 1);
    enif_get_string(env, argv_l, s, len, ERL_NIF_LATIN1);
    return s;
}


static ErlNifFunc nif_funcs[] = {
        {"distance", 2, levenshtein_nif}
};

ERL_NIF_INIT(elevenshtein_nif, nif_funcs, NULL, NULL, NULL, NULL);
