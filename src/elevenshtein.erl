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

%% @doc frontend for levenshtein_nif.

-module(elevenshtein).

-export([distance/2]).

-include_lib("eunit/include/eunit.hrl").

distance(Str1, Str2) when is_list(Str1) ->
    distance(list_to_binary(Str1), Str2);
distance(Str1, Str2) when is_list(Str2) ->
    distance(Str1, list_to_binary(Str2));
distance(Str1, Str2) ->
    elevenshtein_nif:distance(Str1, Str2).

distance_test_() ->
    [
	?_assertEqual(0,  distance(<<"abc">>, <<"abc">>)),
	?_assertEqual(1,  distance(<<"adc">>, <<"abc">>))
    ].
