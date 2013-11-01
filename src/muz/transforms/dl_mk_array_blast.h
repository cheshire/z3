/*++
Copyright (c) 2012 Microsoft Corporation

Module Name:

    dl_mk_array_blast.h

Abstract:

    Remove array variables from rules.

Author:

    Nikolaj Bjorner (nbjorner) 2012-11-23

Revision History:

--*/
#ifndef _DL_MK_ARRAY_BLAST_H_
#define _DL_MK_ARRAY_BLAST_H_

#include"dl_context.h"
#include"dl_rule_set.h"
#include"dl_rule_transformer.h"
#include"dl_mk_interp_tail_simplifier.h"
#include "equiv_proof_converter.h"
#include "array_decl_plugin.h"
#include "expr_safe_replace.h"

namespace datalog {

    /**
       \brief Blast occurrences of arrays in rules
    */
    class mk_array_blast : public rule_transformer::plugin {
        typedef obj_map<app, var*> defs_t;

        context&        m_ctx;
        ast_manager&    m;
        array_util      a;
        rule_manager&   rm;
        params_ref      m_params;
        th_rewriter     m_rewriter;
        mk_interp_tail_simplifier m_simplifier;

        defs_t            m_defs;
        expr_safe_replace m_sub;
        unsigned          m_next_var;

        bool blast(rule& r, rule_set& new_rules);

        bool is_store_def(expr* e, expr*& x, expr*& y);

        bool ackermanize(rule const& r, expr_ref& body, expr_ref& head);

        expr* get_select(expr* e) const;

        void get_select_args(expr* e, ptr_vector<expr>& args) const;

        bool insert_def(rule const& r, app* e, var* v);

    public:
        /**
           \brief Create rule transformer that removes array stores and selects by ackermannization.
        */
        mk_array_blast(context & ctx, unsigned priority);

        virtual ~mk_array_blast();
        
        rule_set * operator()(rule_set const & source);

    };

};

#endif /* _DL_MK_ARRAY_BLAST_H_ */
