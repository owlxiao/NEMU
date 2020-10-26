#include <monitor/difftest.h>

uint32_t pio_read_l(ioaddr_t);
uint32_t pio_read_w(ioaddr_t);
uint32_t pio_read_b(ioaddr_t);
void pio_write_l(ioaddr_t, uint32_t);
void pio_write_w(ioaddr_t, uint32_t);
void pio_write_b(ioaddr_t, uint32_t);

#ifndef __ICS_EXPORT
void load_sreg(int idx, uint16_t val);

static inline def_EHelper(lidt) {
  word_t addr = *s->isa.mbase + s->isa.moff;
  cpu.idtr.limit = vaddr_read(addr, 2);
  cpu.idtr.base = vaddr_read(addr + 2, 4);
  print_asm_template1(lidt);
}

static inline def_EHelper(lgdt) {
  word_t addr = *s->isa.mbase + s->isa.moff;
  cpu.gdtr.limit = vaddr_read(addr, 2);
  cpu.gdtr.base = vaddr_read(addr + 2, 4);
  print_asm_template1(lgdt);
}

static inline def_EHelper(lldt) {
  load_sreg(SR_LDTR, *ddest);
  print_asm_template1(lldt);
}

static inline def_EHelper(mov_r2cr) {
  rtl_lr(s, &cpu.cr[id_dest->reg], id_src1->reg, 4);
  print_asm("movl %%%s,%%cr%d", reg_name(id_src1->reg, 4), id_dest->reg);
}

static inline def_EHelper(mov_cr2r) {
  rtl_sr(s, id_dest->reg, &cpu.cr[id_src1->reg], 4);
  print_asm("movl %%cr%d,%%%s", id_src1->reg, reg_name(id_dest->reg, 4));
}

static inline def_EHelper(mov_rm2sreg) {
  load_sreg(id_dest->reg, *dsrc1);
  if (id_dest->reg == 2) { // SS
#ifndef __DIFF_REF_NEMU__
    difftest_skip_dut(1, 2);
#endif
  }
  print_asm("movw %s,%%%s", id_src1->str, sreg_name(id_dest->reg));
}

static inline def_EHelper(mov_sreg2rm) {
  rtl_li(s, s0, cpu.sreg[id_src1->reg].val);
  operand_write(s, id_dest, s0);
  print_asm("movw %%%s,%s", sreg_name(id_src1->reg), id_dest->str);
}

static inline def_EHelper(push_sreg_internal) {
  rtl_li(s, s0, cpu.sreg[id_dest->reg].val);
  rtl_push(s, s0);
  print_asm("push %%%s", sreg_name(id_dest->reg));
}

static inline def_EHelper(pop_sreg_internal) {
  rtl_pop(s, s0);
  load_sreg(id_dest->reg, *s0);
  print_asm("pop %%%s", sreg_name(id_dest->reg));
}

static inline def_EHelper(push_fs) {
  id_dest->reg = SR_FS;
  exec_push_sreg_internal(s);
}

static inline def_EHelper(push_es) {
  id_dest->reg = SR_ES;
  exec_push_sreg_internal(s);
}

static inline def_EHelper(push_ds) {
  id_dest->reg = SR_DS;
  exec_push_sreg_internal(s);
}

static inline def_EHelper(pop_ds) {
  id_dest->reg = SR_DS;
  exec_pop_sreg_internal(s);
}

static inline def_EHelper(pop_es) {
  id_dest->reg = SR_ES;
  exec_pop_sreg_internal(s);
}

static inline def_EHelper(pop_fs) {
  id_dest->reg = SR_FS;
  exec_pop_sreg_internal(s);
}

static inline def_EHelper(int) {
  void raise_intr(DecodeExecState *s, uint32_t, vaddr_t);
  raise_intr(s, *ddest, s->seq_pc);
  print_asm("int %s", id_dest->str);

#ifndef __DIFF_REF_NEMU__
  difftest_skip_dut(1, 2);
#endif
}

static inline def_EHelper(iret) {
#ifdef __PA__
  rtl_pop(s, s0);  // esp3, customized
#else
  int old_cpl = cpu.sreg[SR_CS].rpl;
#endif
  rtl_pop(s, s1);  // eip
  rtl_jr(s, s1);
  rtl_pop(s, s1);  // cs
  uint16_t new_cs = *s1;
  void rtl_set_eflags(DecodeExecState *s, const rtlreg_t *src);
  rtl_pop(s, s1);  // eflags
  rtl_set_eflags(s, s1);
#ifdef __PA__
  // customized: switch to user stack
  if (*s0 != 0) rtl_mv(s, &cpu.esp, s0);
  difftest_skip_ref();
#else
  int new_cpl = new_cs & 0x3;
  if (new_cpl > old_cpl) {
    // return to user
    rtl_pop(s, s0);  // esp3
    rtl_pop(s, s1);  // ss
    rtl_mv(s, &cpu.esp, s0);
    cpu.sreg[SR_SS].val = *s1;
  }
#endif
  cpu.sreg[SR_CS].val = new_cs;

  print_asm("iret");
}

static inline def_EHelper(in) {
  uint32_t val;
  switch (id_dest->width) {
    case 1: val = pio_read_b(*dsrc1); break;
    case 2: val = pio_read_w(*dsrc1); break;
    case 4: val = pio_read_l(*dsrc1); break;
    default: assert(0);
  }

  rtl_li(s, s0, val);
  operand_write(s, id_dest, s0);

  print_asm_template2(in);
}

static inline def_EHelper(out) {
  switch (id_dest->width) {
    case 1: pio_write_b(*ddest, *dsrc1); break;
    case 2: pio_write_w(*ddest, *dsrc1); break;
    case 4: pio_write_l(*ddest, *dsrc1); break;
    default: assert(0);
  }

  print_asm_template2(out);
}

static inline def_EHelper(invlpg) {
}

static inline def_EHelper(ltr) {
  load_sreg(SR_TR, *ddest);
  print_asm_template1(ltr);
}

static inline def_EHelper(mov_r2dr) {
}


#else
static inline def_EHelper(lidt) {
  TODO();
  print_asm_template1(lidt);
}

static inline def_EHelper(mov_r2cr) {
  TODO();
  print_asm("movl %%%s,%%cr%d", reg_name(id_src1->reg, 4), id_dest->reg);
}

static inline def_EHelper(mov_cr2r) {
  TODO();
  print_asm("movl %%cr%d,%%%s", id_src1->reg, reg_name(id_dest->reg, 4));

#ifndef __DIFF_REF_NEMU__
  difftest_skip_ref();
#endif
}

static inline def_EHelper(int) {
  TODO();
  print_asm("int %s", id_dest->str);

#ifndef __DIFF_REF_NEMU__
  difftest_skip_dut(1, 2);
#endif
}

static inline def_EHelper(iret) {
  TODO();
  print_asm("iret");

#ifndef __DIFF_REF_NEMU__
  difftest_skip_ref();
#endif
}

static inline def_EHelper(in) {
  TODO();
  print_asm_template2(in);
}

static inline def_EHelper(out) {
  TODO();
  print_asm_template2(out);
}
#endif