/* $Id: pe_utils.h,v 1.45 2006/05/05 13:08:49 andrew Exp $ */
/* 
 * Copyright (C) 2004 Andrew Beekhof <andrew@beekhof.net>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef PE_UTILS__H
#define PE_UTILS__H


/* General utilities */
extern resource_t *pe_find_resource(GListPtr rsc_list, const char *id_rh);

extern int merge_weights(int w1, int w2);

/* Constraint helper functions */
extern rsc_colocation_t *invert_constraint(rsc_colocation_t *constraint);

extern rsc_to_node_t *copy_constraint(rsc_to_node_t *constraint);

/* Color helper functions */
extern void add_color_to_rsc(resource_t *rsc, color_t *color);

extern color_t *find_color(GListPtr candidate_colors, color_t *other_color);

extern color_t *create_color(
	pe_working_set_t *data_set, resource_t *resource, GListPtr resources);

extern color_t *copy_color(color_t *a_color);

/* Node helper functions */
extern node_t *pe_find_node_id(GListPtr node_list, const char *id);

extern node_t *node_copy(node_t *this_node) ;


/* Binary like operators for lists of nodes */
extern GListPtr node_list_dup(GListPtr list1, gboolean filter);

extern GListPtr node_list_and(GListPtr list1, GListPtr list2, gboolean filter);

extern GListPtr node_list_xor(GListPtr list1, GListPtr list2, gboolean filter);

extern GListPtr node_list_minus(GListPtr list1,GListPtr list2,gboolean filter);

extern gboolean node_list_eq(GListPtr list1, GListPtr list2, gboolean filter);

extern GListPtr node_list_or(GListPtr list1, GListPtr list2, gboolean filter);



/* For creating the transition graph */
extern crm_data_t *action2xml(action_t *action, gboolean as_input);

/* Printing functions for debug */
extern void print_node(
	const char *pre_text, node_t *node, gboolean details);

extern void print_resource(
	int log_level, const char *pre_text, resource_t *rsc, gboolean details);

extern void print_rsc_to_node(
	const char *pre_text, rsc_to_node_t *cons, gboolean details);

extern void print_rsc_colocation(
	const char *pre_text, rsc_colocation_t *cons, gboolean details);

extern void print_color(
	const char *pre_text, color_t *color, gboolean details);

extern void print_color_details(
	const char *pre_text, struct color_shared_s *color, gboolean details);

extern void log_action(
	unsigned int log_level, const char *pre_text, action_t *action, gboolean details);

/* Sorting functions */
extern gint sort_rsc_priority(gconstpointer a, gconstpointer b);
extern gint sort_rsc_node_weight(gconstpointer a, gconstpointer b);
extern gint sort_cons_strength(gconstpointer a, gconstpointer b);
extern gint sort_color_weight(gconstpointer a, gconstpointer b);
extern gint sort_node_weight(gconstpointer a, gconstpointer b);
extern gint sort_action_id(gconstpointer a, gconstpointer b);

/* enum 2 text functions (mostly used by print_*) */
extern const char *contype2text(enum con_type type);
extern const char *strength2text(enum con_strength strength);

extern const char *task2text(enum action_tasks task);
extern enum action_tasks text2task(const char *task);

extern enum rsc_role_e text2role(const char *role);
extern const char *role2text(enum rsc_role_e role);

extern crm_data_t *find_rsc_op_entry(resource_t *rsc, const char *key);

extern action_t *custom_action(
	resource_t *rsc, char *key, const char *task, node_t *on_node,
	gboolean optional, gboolean foo, pe_working_set_t *data_set);

extern rsc_to_node_t *rsc2node_new(
	const char *id, resource_t *rsc, int weight, node_t *node,
	pe_working_set_t *data_set);

#define delete_key(rsc) generate_op_key(rsc->id, CRMD_ACTION_DELETE, 0)
#define delete_action(rsc, node) custom_action(				\
		rsc, delete_key(rsc), CRMD_ACTION_DELETE, node,		\
		FALSE, TRUE, data_set);

#define stopped_key(rsc) generate_op_key(rsc->id, CRMD_ACTION_STOPPED, 0)
#define stopped_action(rsc, node, optional) custom_action(		\
		rsc, stopped_key(rsc), CRMD_ACTION_STOPPED, node,	\
		optional, TRUE, data_set);

#define stop_key(rsc) generate_op_key(rsc->id, CRMD_ACTION_STOP, 0)
#define stop_action(rsc, node, optional) custom_action(			\
		rsc, stop_key(rsc), CRMD_ACTION_STOP, node,		\
		optional, TRUE, data_set);

#define start_key(rsc) generate_op_key(rsc->id, CRMD_ACTION_START, 0)
#define start_action(rsc, node, optional) custom_action(		\
		rsc, start_key(rsc), CRMD_ACTION_START, node,		\
		optional, TRUE, data_set)

#define started_key(rsc) generate_op_key(rsc->id, CRMD_ACTION_STARTED, 0)
#define started_action(rsc, node, optional) custom_action(		\
		rsc, started_key(rsc), CRMD_ACTION_STARTED, node,	\
		optional, TRUE, data_set)

#define promote_key(rsc) generate_op_key(rsc->id, CRMD_ACTION_PROMOTE, 0)
#define promote_action(rsc, node, optional) custom_action(		\
		rsc, promote_key(rsc), CRMD_ACTION_PROMOTE, node,	\
		optional, TRUE, data_set)

#define promoted_key(rsc) generate_op_key(rsc->id, CRMD_ACTION_PROMOTED, 0)
#define promoted_action(rsc, node, optional) custom_action(		\
		rsc, promoted_key(rsc), CRMD_ACTION_PROMOTED, node,	\
		optional, TRUE, data_set)

#define demote_key(rsc) generate_op_key(rsc->id, CRMD_ACTION_DEMOTE, 0)
#define demote_action(rsc, node, optional) custom_action(		\
		rsc, demote_key(rsc), CRMD_ACTION_DEMOTE, node,		\
		optional, TRUE, data_set)

#define demoted_key(rsc) generate_op_key(rsc->id, CRMD_ACTION_DEMOTED, 0)
#define demoted_action(rsc, node, optional) custom_action(		\
		rsc, demoted_key(rsc), CRMD_ACTION_DEMOTED, node,	\
		optional, TRUE, data_set)

extern GListPtr find_actions(GListPtr input, const char *key, node_t *on_node);
extern GListPtr find_actions_exact(
	GListPtr input, const char *key, node_t *on_node);
extern GListPtr find_recurring_actions(GListPtr input, node_t *not_on_node);

extern void set_id(crm_data_t *xml_obj, const char *prefix, int child);

extern const char *ordering_type2text(enum pe_ordering type);
extern const char *fail2text(enum action_fail_response fail);

extern int char2score(const char *score);
extern char *score2char(int score);


/* free the various structures */
extern void pe_free_nodes(GListPtr nodes);
extern void pe_free_colors(GListPtr colors);
extern void pe_free_rsc_colocation(rsc_colocation_t *cons);
extern void pe_free_rsc_to_node(rsc_to_node_t *cons);
extern void pe_free_shallow(GListPtr alist);
extern void pe_free_shallow_adv(GListPtr alist, gboolean with_data);
extern void pe_free_resources(GListPtr resources);
extern void pe_free_action(action_t *action);
extern void pe_free_actions(GListPtr actions);
extern void pe_free_ordering(GListPtr constraints);

/* Helper macros to avoid NULL pointers */
#define safe_val(def, x,y)          (x?x->y:def)
#define safe_val3(def, t,u,v)       (t?t->u?t->u->v:def:def)
#define safe_val4(def, t,u,v,w)     (t?t->u?t->u->v?t->u->v->w:def:def:def)
#define safe_val5(def, t,u,v,w,x)   (t?t->u?t->u->v?t->u->v->w?t->u->v->w->x:def:def:def:def)
#define safe_val6(def, t,u,v,w,x,y) (t?t->u?t->u->v?t->u->v->w?t->u->v->w->x?t->u->v->w->x->y:def:def:def:def:def)
#define safe_val7(def, t,u,v,w,x,y,z) (t?t->u?t->u->v?t->u->v->w?t->u->v->w->x?t->u->v->w->x->y?t->u->v->w->x->y->z:def:def:def:def:def:def)

#endif
