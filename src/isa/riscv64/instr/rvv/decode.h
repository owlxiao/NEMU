#ifdef CONFIG_RVV_010
#include "vector.h"
// vector
static inline def_DHelper(OP_V) { // 10_101, same to R
  decode_op_r(s, id_src1, s->isa.instr.r.rs1, true);
  decode_op_r(s, id_src2, s->isa.instr.r.rs2, true);
  decode_op_r(s, id_dest, s->isa.instr.r.rd, false);
  // decode_op_r(id_dest, decinfo.isa.instr.v_vd, false);
}

static inline def_DHelper(vsetvl) {
  rtl_li(s, &id_src2->val, s->isa.instr.v_opv2.v_bigbit ? id_src2->val : s->isa.instr.v_opv2.v_zimm);
}

//vector
static inline def_THelper(vopi) {
  def_INSTR_TAB("000000 ? ????? ????? ??? ????? ????? ??", vadd);
  def_INSTR_TAB("000010 ? ????? ????? ??? ????? ????? ??", vsub);
  def_INSTR_TAB("000011 ? ????? ????? ??? ????? ????? ??", vrsub);
  def_INSTR_TAB("000100 ? ????? ????? ??? ????? ????? ??", vminu);
  def_INSTR_TAB("000101 ? ????? ????? ??? ????? ????? ??", vmin);
  def_INSTR_TAB("000110 ? ????? ????? ??? ????? ????? ??", vmaxu);
  def_INSTR_TAB("000111 ? ????? ????? ??? ????? ????? ??", vmax);
  def_INSTR_TAB("001001 ? ????? ????? ??? ????? ????? ??", vand);
  def_INSTR_TAB("001010 ? ????? ????? ??? ????? ????? ??", vor);
  def_INSTR_TAB("001011 ? ????? ????? ??? ????? ????? ??", vxor);
  def_INSTR_TAB("001100 ? ????? ????? ??? ????? ????? ??", vrgather);
  def_INSTR_TAB("001110 ? ????? ????? ??? ????? ????? ??", vslideup);
  def_INSTR_TAB("001111 ? ????? ????? ??? ????? ????? ??", vslidedown);
  def_INSTR_TAB("010000 ? ????? ????? ??? ????? ????? ??", vadc);
  def_INSTR_TAB("010001 ? ????? ????? ??? ????? ????? ??", vmadc);
  def_INSTR_TAB("010010 ? ????? ????? ??? ????? ????? ??", vsbc);
  def_INSTR_TAB("010011 ? ????? ????? ??? ????? ????? ??", vmsbc);
  def_INSTR_TAB("010111 ? ????? ????? ??? ????? ????? ??", vmerge);
  def_INSTR_TAB("011000 ? ????? ????? ??? ????? ????? ??", vmseq);
  def_INSTR_TAB("011001 ? ????? ????? ??? ????? ????? ??", vmsne);
  def_INSTR_TAB("011010 ? ????? ????? ??? ????? ????? ??", vmsltu;
  def_INSTR_TAB("011011 ? ????? ????? ??? ????? ????? ??", vmslt);
  def_INSTR_TAB("011100 ? ????? ????? ??? ????? ????? ??", vmsleu);
  def_INSTR_TAB("011101 ? ????? ????? ??? ????? ????? ??", vmsle);
  def_INSTR_TAB("011110 ? ????? ????? ??? ????? ????? ??", vmsgtu);
  def_INSTR_TAB("011111 ? ????? ????? ??? ????? ????? ??", vmsgt);
  def_INSTR_TAB("100000 ? ????? ????? ??? ????? ????? ??", vsaddu);
  def_INSTR_TAB("100001 ? ????? ????? ??? ????? ????? ??", vsadd);
  def_INSTR_TAB("100010 ? ????? ????? ??? ????? ????? ??", vssubu);
  def_INSTR_TAB("100011 ? ????? ????? ??? ????? ????? ??", vssub);
  def_INSTR_TAB("100100 ? ????? ????? ??? ????? ????? ??", vaadd);
  def_INSTR_TAB("100101 ? ????? ????? ??? ????? ????? ??", vsll);
  def_INSTR_TAB("100110 ? ????? ????? ??? ????? ????? ??", vasub);
  def_INSTR_TAB("100111 ? ????? ????? ??? ????? ????? ??", vsmul);
  def_INSTR_TAB("101000 ? ????? ????? ??? ????? ????? ??", vsrl);
  def_INSTR_TAB("101001 ? ????? ????? ??? ????? ????? ??", vsra);
  def_INSTR_TAB("101010 ? ????? ????? ??? ????? ????? ??", vssrl);
  def_INSTR_TAB("101011 ? ????? ????? ??? ????? ????? ??", vssra);
  def_INSTR_TAB("101100 ? ????? ????? ??? ????? ????? ??", vnsrl);
  def_INSTR_TAB("101101 ? ????? ????? ??? ????? ????? ??", vnsra);
  def_INSTR_TAB("101110 ? ????? ????? ??? ????? ????? ??", vnclipu);
  def_INSTR_TAB("101111 ? ????? ????? ??? ????? ????? ??", vnclip);
  def_INSTR_TAB("101010 ? ????? ????? ??? ????? ????? ??", vssrl);
  def_INSTR_TAB("110000 ? ????? ????? ??? ????? ????? ??", vwredsumu);
  def_INSTR_TAB("110001 ? ????? ????? ??? ????? ????? ??", vwredsum);
  def_INSTR_TAB("111000 ? ????? ????? ??? ????? ????? ??", vdotu);
  def_INSTR_TAB("111001 ? ????? ????? ??? ????? ????? ??", vdot);
  def_INSTR_TAB("111100 ? ????? ????? ??? ????? ????? ??", vwsmaccu);
  def_INSTR_TAB("111101 ? ????? ????? ??? ????? ????? ??", vwsmacc);
  def_INSTR_TAB("111110 ? ????? ????? ??? ????? ????? ??", vwsmaccsu);
  def_INSTR_TAB("111111 ? ????? ????? ??? ????? ????? ??", vwsmaccus);
  
  return EXEC_ID_inv;
  //longjmp_raise_intr(EX_II);
}

static inline def_THelper(vopm) {
  def_INSTR_TAB("000000 ? ????? ????? ??? ????? ????? ??", vredsum);
  def_INSTR_TAB("000001 ? ????? ????? ??? ????? ????? ??", vredand);
  def_INSTR_TAB("000010 ? ????? ????? ??? ????? ????? ??", vredor);
  def_INSTR_TAB("000011 ? ????? ????? ??? ????? ????? ??", vredxor);
  def_INSTR_TAB("000100 ? ????? ????? ??? ????? ????? ??", vredminu);
  def_INSTR_TAB("000101 ? ????? ????? ??? ????? ????? ??", vredmin);
  def_INSTR_TAB("000110 ? ????? ????? ??? ????? ????? ??", vredmaxu);
  def_INSTR_TAB("000111 ? ????? ????? ??? ????? ????? ??", vredmax);
  
  def_INSTR_TAB("010100 ? ????? ????? ??? ????? ????? ??", vmpopc);
  def_INSTR_TAB("010101 ? ????? ????? ??? ????? ????? ??", vmfirst);
  def_INSTR_TAB("010110 ? ????? ????? ??? ????? ????? ??", vmunaryo);
  def_INSTR_TAB("010111 ? ????? ????? ??? ????? ????? ??", vcompress);
  def_INSTR_TAB("011000 ? ????? ????? ??? ????? ????? ??", vmandnot);
  def_INSTR_TAB("011001 ? ????? ????? ??? ????? ????? ??", vmand);
  def_INSTR_TAB("011010 ? ????? ????? ??? ????? ????? ??", vmor);
  def_INSTR_TAB("011011 ? ????? ????? ??? ????? ????? ??", vmxor);
  def_INSTR_TAB("011100 ? ????? ????? ??? ????? ????? ??", vmornot);
  def_INSTR_TAB("011101 ? ????? ????? ??? ????? ????? ??", vmnand);
  def_INSTR_TAB("011110 ? ????? ????? ??? ????? ????? ??", vmnor);
  def_INSTR_TAB("011111 ? ????? ????? ??? ????? ????? ??", vmxnor);
  def_INSTR_TAB("100000 ? ????? ????? ??? ????? ????? ??", vdivu);
  def_INSTR_TAB("100001 ? ????? ????? ??? ????? ????? ??", vdiv);
  def_INSTR_TAB("100010 ? ????? ????? ??? ????? ????? ??", vremu);
  def_INSTR_TAB("100011 ? ????? ????? ??? ????? ????? ??", vrem);
  def_INSTR_TAB("100100 ? ????? ????? ??? ????? ????? ??", vmulhu);
  def_INSTR_TAB("100101 ? ????? ????? ??? ????? ????? ??", vmul);
  def_INSTR_TAB("100110 ? ????? ????? ??? ????? ????? ??", vmulhsu);
  def_INSTR_TAB("100111 ? ????? ????? ??? ????? ????? ??", vmulh);
  def_INSTR_TAB("101001 ? ????? ????? ??? ????? ????? ??", vmadd);
  def_INSTR_TAB("101010 ? ????? ????? ??? ????? ????? ??", vnmsub);
  def_INSTR_TAB("101101 ? ????? ????? ??? ????? ????? ??", vmacc);
  def_INSTR_TAB("101111 ? ????? ????? ??? ????? ????? ??", vnmsac);
  def_INSTR_TAB("110000 ? ????? ????? ??? ????? ????? ??", vwaddu);
  def_INSTR_TAB("110001 ? ????? ????? ??? ????? ????? ??", vwadd);
  def_INSTR_TAB("110010 ? ????? ????? ??? ????? ????? ??", vwsubu);
  def_INSTR_TAB("110011 ? ????? ????? ??? ????? ????? ??", vwsub);
  def_INSTR_TAB("110100 ? ????? ????? ??? ????? ????? ??", vwaddu_w);
  def_INSTR_TAB("110101 ? ????? ????? ??? ????? ????? ??", vwadd_w);
  def_INSTR_TAB("110110 ? ????? ????? ??? ????? ????? ??", vwsubu_w);
  def_INSTR_TAB("110111 ? ????? ????? ??? ????? ????? ??", vwsub_w);
  def_INSTR_TAB("111000 ? ????? ????? ??? ????? ????? ??", vwmulu);
  def_INSTR_TAB("111010 ? ????? ????? ??? ????? ????? ??", vwmulsu);
  def_INSTR_TAB("111011 ? ????? ????? ??? ????? ????? ??", vwmul);
  def_INSTR_TAB("111100 ? ????? ????? ??? ????? ????? ??", vwmaccu);
  def_INSTR_TAB("111101 ? ????? ????? ??? ????? ????? ??", vwnmacc);
  def_INSTR_TAB("111110 ? ????? ????? ??? ????? ????? ??", vwmaccsu);
  def_INSTR_TAB("111111 ? ????? ????? ??? ????? ????? ??", vwmaccus);

  return EXEC_ID_inv;
  }
}

static inline def_THelper(vopf) {
  // longjmp_raise_intr(EX_II);
  return EXEC_ID_inv;
}

// All RVV instructions decode start from here
static inline def_THelper(OP_V) { // 10_101
  switch (s->isa.instr.i.funct3) {
    case 0 : s->src_vmode = SRC_VV; break;
    case 1 : s->src_vmode = SRC_VV; break;
    case 2 : s->src_vmode = SRC_VV; break;
    case 3 : s->src_vmode = SRC_VI; break;
    case 4 : s->src_vmode = SRC_VS; break;
    case 5 : s->src_vmode = SRC_VS; break;
    case 6 : s->src_vmode = SRC_VS; break;
    case 7 : s->src_vmode = SRC_SI; break;
    default: exec_inv(s);
  }

  s->width = 1 << vtype->vsew;
  s->vm = s->isa.instr.v_opv1.v_vm; //1 for without mask; 0 for with mask

  /*
  switch(s->isa.instr.i.funct3) {
    EX(0x0, vopi) EX(0x1, vopf) EX(0x2, vopm) EX(0x3, vopi) EX(0x4, vopi) EX(0x5, vopf) EX(0x6, vopm) IDEX(0x7, vsetvl, vsetvl)
  }
  */
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", vopi);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", vopf);
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", vopm);
  def_INSTR_TAB("??????? ????? ????? 011 ????? ????? ??", vopi);
  def_INSTR_TAB("??????? ????? ????? 100 ????? ????? ??", vopi);
  def_INSTR_TAB("??????? ????? ????? 101 ????? ????? ??", vopf);
  def_INSTR_TAB("??????? ????? ????? 110 ????? ????? ??", vopm);
  def_INSTR_IDTAB("??????? ????? ????? 111 ????? ????? ??", vsetvl, vsetvl);
}

#endif // CONFIG_RVV_010