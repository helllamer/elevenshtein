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

extern int levenshtein_distance_len (const char*, int, const char*, int);

// NIF-wrapper for distance calculation.
// $1, $2 = binary()
static ERL_NIF_TERM levenshtein_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ErlNifBinary s1, s2;

    if(!(enif_inspect_binary(env, argv[0], &s1) && enif_inspect_binary(env, argv[1], &s2))) {
	return enif_make_badarg(env);
    };

    int d = levenshtein_distance_len((const char *)s1.data, s1.size, (const char *)s2.data, s2.size);
    return enif_make_int(env, d);
}


static ErlNifFunc nif_funcs[] = {
    {"distance", 2, levenshtein_nif}
};


static int load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM load_info) {
    return 0;
}

static int reload(ErlNifEnv* env, void** priv, ERL_NIF_TERM load_info) {
    return load(env, priv, load_info);
}

static int upgrade(ErlNifEnv* env, void** priv, void** old_priv, ERL_NIF_TERM load_info) {
    return 0;
}

static void unload(ErlNifEnv* env, void* priv) {
    return;
}

ERL_NIF_INIT(elevenshtein_nif, nif_funcs, load, reload, upgrade, unload);
