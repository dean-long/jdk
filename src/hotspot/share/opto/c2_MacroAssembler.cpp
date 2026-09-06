/*
 * Copyright (c) 2026, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#include "opto/c2_MacroAssembler.hpp"
#include "opto/compile.hpp"
#include "opto/output.hpp"
#include "opto/regalloc.hpp"
#include "utilities/globalDefinitions.hpp"
#include "utilities/macros.hpp"

class C2EntryBarrierStub;
class TypeInt;
class TypeLong;

int C2_MacroAssembler::fixed_slot_offset(Compile* C, int slot) {
  PhaseRegAlloc* ra = C->regalloc();
  OptoReg::Name reg = OptoReg::stack2reg(slot);
  return ra->reg2offset_unchecked(reg);
}

int C2_MacroAssembler::stack_increment_offset(Compile* C) {
  assert(C->needs_stack_repair(), "no stack increment slot?");
  // This slot must be last, so CPU-specific code can find it
  // at the end the frame.
  int slot = C->stack_increment_slot();
  assert(slot == C->fixed_slots() - VMRegImpl::slots_per_word, "must be last");
  return fixed_slot_offset(C, slot);
}
