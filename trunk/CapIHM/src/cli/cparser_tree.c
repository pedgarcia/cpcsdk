/*----------------------------------------------------------------------
 * This file is generated by mk_parser.py.
 *----------------------------------------------------------------------*/
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "cparser.h"
#include "cparser_priv.h"
#include "cparser_token.h"
#include "cparser_tree.h"

cparser_result_t
cparser_glue_show_registers (cparser_t *parser)
{
    cparser_cmd_show_registers(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_show_registers_crtc (cparser_t *parser)
{
    cparser_cmd_show_registers_crtc(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_show_registers_ga (cparser_t *parser)
{
    cparser_cmd_show_registers_ga(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_show_registers_z80 (cparser_t *parser)
{
    cparser_cmd_show_registers_z80(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_breakpoints_add_adress (cparser_t *parser)
{
    uint32_t adress_val;
    uint32_t *adress_ptr = NULL;
    cparser_result_t rc;

    rc = cparser_get_uint(&parser->tokens[2], &adress_val);
    assert(CPARSER_OK == rc);
    adress_ptr = &adress_val;
    cparser_cmd_breakpoints_add_adress(&parser->context,
        adress_ptr);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_breakpoints_remove_adress (cparser_t *parser)
{
    uint32_t adress_val;
    uint32_t *adress_ptr = NULL;
    cparser_result_t rc;

    rc = cparser_get_uint(&parser->tokens[2], &adress_val);
    assert(CPARSER_OK == rc);
    adress_ptr = &adress_val;
    cparser_cmd_breakpoints_remove_adress(&parser->context,
        adress_ptr);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_breakpoints_list (cparser_t *parser)
{
    cparser_cmd_breakpoints_list(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_continue (cparser_t *parser)
{
    cparser_cmd_continue(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_step (cparser_t *parser)
{
    cparser_cmd_step(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_video_color_on (cparser_t *parser)
{
    cparser_cmd_video_color_on(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_video_color_grey (cparser_t *parser)
{
    cparser_cmd_video_color_grey(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_video_color_green (cparser_t *parser)
{
    cparser_cmd_video_color_green(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_memory_poke_address_value (cparser_t *parser)
{
    uint32_t address_val;
    uint32_t *address_ptr = NULL;
    uint32_t value_val;
    uint32_t *value_ptr = NULL;
    cparser_result_t rc;

    rc = cparser_get_uint(&parser->tokens[2], &address_val);
    assert(CPARSER_OK == rc);
    address_ptr = &address_val;
    rc = cparser_get_uint(&parser->tokens[3], &value_val);
    assert(CPARSER_OK == rc);
    value_ptr = &value_val;
    cparser_cmd_memory_poke_address_value(&parser->context,
        address_ptr,
        value_ptr);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_memory_peek_address (cparser_t *parser)
{
    uint32_t address_val;
    uint32_t *address_ptr = NULL;
    cparser_result_t rc;

    rc = cparser_get_uint(&parser->tokens[2], &address_val);
    assert(CPARSER_OK == rc);
    address_ptr = &address_val;
    cparser_cmd_memory_peek_address(&parser->context,
        address_ptr);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_memory_disassemble_address_quantity (cparser_t *parser)
{
    uint32_t address_val;
    uint32_t *address_ptr = NULL;
    uint32_t quantity_val;
    uint32_t *quantity_ptr = NULL;
    cparser_result_t rc;

    rc = cparser_get_uint(&parser->tokens[2], &address_val);
    assert(CPARSER_OK == rc);
    address_ptr = &address_val;
    rc = cparser_get_uint(&parser->tokens[3], &quantity_val);
    if (CPARSER_OK == rc) {
        quantity_ptr = &quantity_val;
    } else {
        assert(4 > parser->token_tos);
    }
    cparser_cmd_memory_disassemble_address_quantity(&parser->context,
        address_ptr,
        quantity_ptr);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_memory_disassemble_pc_quantity (cparser_t *parser)
{
    uint32_t quantity_val;
    uint32_t *quantity_ptr = NULL;
    cparser_result_t rc;

    rc = cparser_get_uint(&parser->tokens[3], &quantity_val);
    if (CPARSER_OK == rc) {
        quantity_ptr = &quantity_val;
    } else {
        assert(4 > parser->token_tos);
    }
    cparser_cmd_memory_disassemble_pc_quantity(&parser->context,
        quantity_ptr);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_quit (cparser_t *parser)
{
    cparser_cmd_quit(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_reset (cparser_t *parser)
{
    cparser_cmd_reset(&parser->context);
    return CPARSER_OK;
}

cparser_result_t
cparser_glue_help_filter (cparser_t *parser)
{
    char *filter_val;
    char **filter_ptr = NULL;
    cparser_result_t rc;

    rc = cparser_get_string(&parser->tokens[1], &filter_val);
    if (CPARSER_OK == rc) {
        filter_ptr = &filter_val;
    } else {
        assert(2 > parser->token_tos);
    }
    cparser_cmd_help_filter(&parser->context,
        filter_ptr);
    return CPARSER_OK;
}

cparser_node_t cparser_node_help_filter_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_help_filter,
    "Show help",
    NULL,
    NULL
};
cparser_node_t cparser_node_help_filter = {
    CPARSER_NODE_STRING,
    CPARSER_NODE_FLAGS_OPT_END,
    "<STRING:filter>",
    NULL,
    NULL,
    &cparser_node_help_filter_eol
};
cparser_node_t cparser_node_help_eol = {
    CPARSER_NODE_END,
    CPARSER_NODE_FLAGS_OPT_PARTIAL,
    cparser_glue_help_filter,
    NULL,
    &cparser_node_help_filter,
    NULL
};
cparser_node_t cparser_node_help = {
    CPARSER_NODE_KEYWORD,
    CPARSER_NODE_FLAGS_OPT_START,
    "help",
    NULL,
    NULL,
    &cparser_node_help_eol
};
cparser_node_t cparser_node_reset_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_reset,
    "Reset emu",
    NULL,
    NULL
};
cparser_node_t cparser_node_reset = {
    CPARSER_NODE_KEYWORD,
    0,
    "reset",
    NULL,
    &cparser_node_help,
    &cparser_node_reset_eol
};
cparser_node_t cparser_node_quit_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_quit,
    "Quit Caprice",
    NULL,
    NULL
};
cparser_node_t cparser_node_quit = {
    CPARSER_NODE_KEYWORD,
    0,
    "quit",
    NULL,
    &cparser_node_reset,
    &cparser_node_quit_eol
};
cparser_node_t cparser_node_memory_disassemble_pc_quantity_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_memory_disassemble_pc_quantity,
    "Disassemble memory at pc",
    NULL,
    NULL
};
cparser_node_t cparser_node_memory_disassemble_pc_quantity = {
    CPARSER_NODE_UINT,
    CPARSER_NODE_FLAGS_OPT_END,
    "<UINT:quantity>",
    NULL,
    NULL,
    &cparser_node_memory_disassemble_pc_quantity_eol
};
cparser_node_t cparser_node_memory_disassemble_pc_eol = {
    CPARSER_NODE_END,
    CPARSER_NODE_FLAGS_OPT_PARTIAL,
    cparser_glue_memory_disassemble_pc_quantity,
    NULL,
    &cparser_node_memory_disassemble_pc_quantity,
    NULL
};
cparser_node_t cparser_node_memory_disassemble_pc = {
    CPARSER_NODE_KEYWORD,
    CPARSER_NODE_FLAGS_OPT_START,
    "pc",
    NULL,
    NULL,
    &cparser_node_memory_disassemble_pc_eol
};
cparser_node_t cparser_node_memory_disassemble_address_quantity_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_memory_disassemble_address_quantity,
    "Disassemble memory",
    NULL,
    NULL
};
cparser_node_t cparser_node_memory_disassemble_address_quantity = {
    CPARSER_NODE_UINT,
    CPARSER_NODE_FLAGS_OPT_END | CPARSER_NODE_FLAGS_OPT_END,
    "<UINT:quantity>",
    NULL,
    NULL,
    &cparser_node_memory_disassemble_address_quantity_eol
};
cparser_node_t cparser_node_memory_disassemble_address_eol = {
    CPARSER_NODE_END,
    CPARSER_NODE_FLAGS_OPT_PARTIAL,
    cparser_glue_memory_disassemble_address_quantity,
    NULL,
    &cparser_node_memory_disassemble_address_quantity,
    NULL
};
cparser_node_t cparser_node_memory_disassemble_address = {
    CPARSER_NODE_UINT,
    CPARSER_NODE_FLAGS_OPT_START,
    "<UINT:address>",
    NULL,
    &cparser_node_memory_disassemble_pc,
    &cparser_node_memory_disassemble_address_eol
};
cparser_node_t cparser_node_memory_disassemble_eol = {
    CPARSER_NODE_END,
    CPARSER_NODE_FLAGS_OPT_PARTIAL,
    cparser_glue_memory_disassemble_address_quantity,
    NULL,
    &cparser_node_memory_disassemble_address,
    NULL
};
cparser_node_t cparser_node_memory_disassemble = {
    CPARSER_NODE_KEYWORD,
    CPARSER_NODE_FLAGS_OPT_START,
    "disassemble",
    NULL,
    NULL,
    &cparser_node_memory_disassemble_eol
};
cparser_node_t cparser_node_memory_peek_address_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_memory_peek_address,
    "Read a byte in memory",
    NULL,
    NULL
};
cparser_node_t cparser_node_memory_peek_address = {
    CPARSER_NODE_UINT,
    0,
    "<UINT:address>",
    NULL,
    NULL,
    &cparser_node_memory_peek_address_eol
};
cparser_node_t cparser_node_memory_peek = {
    CPARSER_NODE_KEYWORD,
    0,
    "peek",
    NULL,
    &cparser_node_memory_disassemble,
    &cparser_node_memory_peek_address
};
cparser_node_t cparser_node_memory_poke_address_value_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_memory_poke_address_value,
    "Poke a byte (or word) in memory",
    NULL,
    NULL
};
cparser_node_t cparser_node_memory_poke_address_value = {
    CPARSER_NODE_UINT,
    0,
    "<UINT:value>",
    NULL,
    NULL,
    &cparser_node_memory_poke_address_value_eol
};
cparser_node_t cparser_node_memory_poke_address = {
    CPARSER_NODE_UINT,
    0,
    "<UINT:address>",
    NULL,
    NULL,
    &cparser_node_memory_poke_address_value
};
cparser_node_t cparser_node_memory_poke = {
    CPARSER_NODE_KEYWORD,
    0,
    "poke",
    NULL,
    &cparser_node_memory_peek,
    &cparser_node_memory_poke_address
};
cparser_node_t cparser_node_memory = {
    CPARSER_NODE_KEYWORD,
    0,
    "memory",
    NULL,
    &cparser_node_quit,
    &cparser_node_memory_poke
};
cparser_node_t cparser_node_video_color_green_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_video_color_green,
    "put screen in greenscale",
    NULL,
    NULL
};
cparser_node_t cparser_node_video_color_green = {
    CPARSER_NODE_KEYWORD,
    0,
    "green",
    NULL,
    NULL,
    &cparser_node_video_color_green_eol
};
cparser_node_t cparser_node_video_color_grey_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_video_color_grey,
    "put screen in greyscale",
    NULL,
    NULL
};
cparser_node_t cparser_node_video_color_grey = {
    CPARSER_NODE_KEYWORD,
    0,
    "grey",
    NULL,
    &cparser_node_video_color_green,
    &cparser_node_video_color_grey_eol
};
cparser_node_t cparser_node_video_color_on_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_video_color_on,
    "put screen in color ",
    NULL,
    NULL
};
cparser_node_t cparser_node_video_color_on = {
    CPARSER_NODE_KEYWORD,
    0,
    "on",
    NULL,
    &cparser_node_video_color_grey,
    &cparser_node_video_color_on_eol
};
cparser_node_t cparser_node_video_color = {
    CPARSER_NODE_KEYWORD,
    0,
    "color",
    NULL,
    NULL,
    &cparser_node_video_color_on
};
cparser_node_t cparser_node_video = {
    CPARSER_NODE_KEYWORD,
    0,
    "video",
    NULL,
    &cparser_node_memory,
    &cparser_node_video_color
};
cparser_node_t cparser_node_step_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_step,
    "Step execute step by step",
    NULL,
    NULL
};
cparser_node_t cparser_node_step = {
    CPARSER_NODE_KEYWORD,
    0,
    "step",
    NULL,
    &cparser_node_video,
    &cparser_node_step_eol
};
cparser_node_t cparser_node_continue_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_continue,
    "Continue program execution",
    NULL,
    NULL
};
cparser_node_t cparser_node_continue = {
    CPARSER_NODE_KEYWORD,
    0,
    "continue",
    NULL,
    &cparser_node_step,
    &cparser_node_continue_eol
};
cparser_node_t cparser_node_breakpoints_list_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_breakpoints_list,
    "List all breakpoints",
    NULL,
    NULL
};
cparser_node_t cparser_node_breakpoints_list = {
    CPARSER_NODE_KEYWORD,
    0,
    "list",
    NULL,
    NULL,
    &cparser_node_breakpoints_list_eol
};
cparser_node_t cparser_node_breakpoints_remove_adress_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_breakpoints_remove_adress,
    "Remove a breakpoint",
    NULL,
    NULL
};
cparser_node_t cparser_node_breakpoints_remove_adress = {
    CPARSER_NODE_UINT,
    0,
    "<UINT:adress>",
    NULL,
    NULL,
    &cparser_node_breakpoints_remove_adress_eol
};
cparser_node_t cparser_node_breakpoints_remove = {
    CPARSER_NODE_KEYWORD,
    0,
    "remove",
    NULL,
    &cparser_node_breakpoints_list,
    &cparser_node_breakpoints_remove_adress
};
cparser_node_t cparser_node_breakpoints_add_adress_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_breakpoints_add_adress,
    "Add a breakpoint in the memory",
    NULL,
    NULL
};
cparser_node_t cparser_node_breakpoints_add_adress = {
    CPARSER_NODE_UINT,
    0,
    "<UINT:adress>",
    NULL,
    NULL,
    &cparser_node_breakpoints_add_adress_eol
};
cparser_node_t cparser_node_breakpoints_add = {
    CPARSER_NODE_KEYWORD,
    0,
    "add",
    NULL,
    &cparser_node_breakpoints_remove,
    &cparser_node_breakpoints_add_adress
};
cparser_node_t cparser_node_breakpoints = {
    CPARSER_NODE_KEYWORD,
    0,
    "breakpoints",
    NULL,
    &cparser_node_continue,
    &cparser_node_breakpoints_add
};
cparser_node_t cparser_node_show_registers_z80_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_show_registers_z80,
    "List Z80 registers",
    NULL,
    NULL
};
cparser_node_t cparser_node_show_registers_z80 = {
    CPARSER_NODE_KEYWORD,
    0,
    "z80",
    NULL,
    NULL,
    &cparser_node_show_registers_z80_eol
};
cparser_node_t cparser_node_show_registers_ga_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_show_registers_ga,
    "List GA registers values",
    NULL,
    NULL
};
cparser_node_t cparser_node_show_registers_ga = {
    CPARSER_NODE_KEYWORD,
    0,
    "ga",
    NULL,
    &cparser_node_show_registers_z80,
    &cparser_node_show_registers_ga_eol
};
cparser_node_t cparser_node_show_registers_crtc_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_show_registers_crtc,
    "List CRTC registers values",
    NULL,
    NULL
};
cparser_node_t cparser_node_show_registers_crtc = {
    CPARSER_NODE_KEYWORD,
    0,
    "crtc",
    NULL,
    &cparser_node_show_registers_ga,
    &cparser_node_show_registers_crtc_eol
};
cparser_node_t cparser_node_show_registers_eol = {
    CPARSER_NODE_END,
    0,
    cparser_glue_show_registers,
    "List registers values",
    &cparser_node_show_registers_crtc,
    NULL
};
cparser_node_t cparser_node_show_registers = {
    CPARSER_NODE_KEYWORD,
    0,
    "registers",
    NULL,
    NULL,
    &cparser_node_show_registers_eol
};
cparser_node_t cparser_node_show = {
    CPARSER_NODE_KEYWORD,
    0,
    "show",
    NULL,
    &cparser_node_breakpoints,
    &cparser_node_show_registers
};
cparser_node_t cparser_root = {
    CPARSER_NODE_ROOT,
    0,
    NULL,
    "Root node of the parser tree",
    NULL,
    &cparser_node_show
};
