ERL          ?= erl
EBIN_DIRS    := $(wildcard deps/*/ebin)
APP          := ebot
REBAR	     := ./rebar

all: erl

get_deps:
	$(REBAR) get-deps

erl:
	$(REBAR) compile

docs:
	@erl -noshell -run edoc_run application '$(APP)' '"."' '[]'

clean: 
	$(REBAR) clean
