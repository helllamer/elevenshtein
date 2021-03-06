%% Copyright 2012 Konstantin Nikiforov <helllamer@gmail.com>
%%
%% Licensed under the Apache License, Version 2.0 (the "License");
%% you may not use this file except in compliance with the License.
%% You may obtain a copy of the License at
%%
%%     http://www.apache.org/licenses/LICENSE-2.0
%%
%% Unless required by applicable law or agreed to in writing, software
%% distributed under the License is distributed on an "AS IS" BASIS,
%% WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
%% See the License for the specific language governing permissions and
%% limitations under the License.

-module(elevenshtein_nif).
-export([distance/2]).
-on_load(init/0).

init() ->
    NifSo = filename:join(
	code:priv_dir(elevenshtein), ?MODULE_STRING
    ),
    ok = erlang:load_nif(NifSo, 0).


distance(_,_) ->
    exit(nif_library_not_loaded).
