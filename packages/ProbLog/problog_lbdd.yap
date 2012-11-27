%
% ProbLog extension to use an YAP BDD interface module, instead of simplecudd.
%


:- use_module(library(trie_sp)).
:- use_module(library(bdd)).
:- use_module(library(bhash)).

problog_kbest_bdd(Goal, K, Prob, ok) :-
	problog_kbest_to_bdd(Goal, K, BDD, MapList),
	bind_maplist(MapList, BoundVars),
	bdd_to_probability_sum_product(BDD, BoundVars, Prob).

problog_kbest_as_bdd(Goal, K, bdd(Tree, MapList)) :-
	problog_kbest_to_bdd(Goal, K, BDD, MapList),
	bdd_tree(BDD, bdd(_Dir, Tree, _Vars)),
	bdd_close(BDD).

problog_kbest_to_bdd(Goal, K, BDD, MapList) :-
	problog_flag(first_threshold,InitT),
	init_problog_kbest(InitT),
	problog_control(off,up),
	problog_kbest_id(Goal, K),
	retract(current_kbest(_,ListFound,_NumFound)),
	build_prefixtree(ListFound),
	nb_getval(problog_completed_proofs, Trie_Completed_Proofs),
	trie_to_bdd(Trie_Completed_Proofs, BDD, MapList),
	delete_ptree(Trie_Completed_Proofs).

problog_fl_bdd(Goal,  _) :-
	init_problog_low(0.0),
	problog_control(off, up),
	timer_start(sld_time),
	problog_call(Goal),
	add_solution,
	fail.
problog_fl_bdd(_,Prob) :-
	timer_stop(sld_time,SLD_Time),
	problog_var_set(sld_time, SLD_Time),
	nb_getval(problog_completed_proofs, Trie_Completed_Proofs),
	tabled_trie_to_bdd(Trie_Completed_Proofs, BDD, MapList),
	bind_maplist(MapList, BoundVars),
	bdd_to_probability_sum_product(BDD, BoundVars, Prob),
	(problog_flag(retain_tables, true) -> retain_tabling; true),
	clear_tabling.

bind_maplist([], []).
bind_maplist([Node-_|MapList], [ProbFact|BoundVars]) :-
	get_fact_probability(Node,ProbFact),
	bind_maplist(MapList, BoundVars).

