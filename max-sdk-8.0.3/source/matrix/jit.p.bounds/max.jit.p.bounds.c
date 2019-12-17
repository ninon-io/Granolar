/*
	Copyright 2001-2005 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_p_bounds
{
	t_object		ob;
	void			*obex;
} t_max_jit_p_bounds;

t_jit_err jit_p_bounds_init(void);

void *max_jit_p_bounds_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_p_bounds_free(t_max_jit_p_bounds *x);
t_messlist *max_jit_p_bounds_class;

void ext_main(void *r)
{
	void *p,*q;

	jit_p_bounds_init();
	setup(&max_jit_p_bounds_class, max_jit_p_bounds_new, (method)max_jit_p_bounds_free, (short)sizeof(t_max_jit_p_bounds),
		  0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_p_bounds,obex));
	q = jit_class_findbyname(gensym("jit_p_bounds"));
	max_jit_classex_mop_wrap(p,q,MAX_JIT_MOP_FLAGS_OWN_ADAPT);
	max_jit_classex_standard_wrap(p,q,0);
	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);
}

void max_jit_p_bounds_free(t_max_jit_p_bounds *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_p_bounds_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_p_bounds *x;
	void *o;

	if (x=(t_max_jit_p_bounds *)max_jit_obex_new(max_jit_p_bounds_class,gensym("jit_p_bounds"))) {
		if (o=jit_object_new(gensym("jit_p_bounds"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.p.bounds: could not allocate object");
			freeobject((t_object *) x);
			x = NULL;
		}
	}
	return (x);
}