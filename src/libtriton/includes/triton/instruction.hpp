//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#ifndef TRITON_INSTRUCTION_H
#define TRITON_INSTRUCTION_H

#include <list>
#include <map>
#include <ostream>
#include <sstream>
#include <utility>
#include <vector>

#include <triton/ast.hpp>
#include <triton/dllexport.hpp>
#include <triton/memoryAccess.hpp>
#include <triton/operandWrapper.hpp>
#include <triton/register.hpp>
#include <triton/symbolicExpression.hpp>
#include <triton/tritonTypes.hpp>



//! The Triton namespace
namespace triton {
/*!
 *  \addtogroup triton
 *  @{
 */

  //! The Triton namespace
  namespace arch {
  /*!
   *  \ingroup triton
   *  \addtogroup arch
   *  @{
   */

    /*! \class Instruction
     *  \brief This class is used when to represent an instruction
     */
    class Instruction {
      protected:
        //! The thread id of the instruction.
        triton::uint32 tid;

        //! The address of the instruction.
        triton::uint64 address;

        //! The disassembly of the instruction. This field is set at the disassembly level.
        std::stringstream disassembly;

        //! The opcode of the instruction.
        triton::uint8 opcode[32];

        //! The size of the instruction.
        triton::uint32 size;

        //! The type of the instruction. This field is set at the disassembly level.
        triton::uint32 type;

        //! The prefix of the instruction. This field is set at the disassembly level.
        triton::uint32 prefix;

        //! Implicit and explicit load access (read). This field is set at the semantics level.
        std::set<std::pair<triton::arch::MemoryAccess, triton::ast::AbstractNode*>> loadAccess;

        //! Implicit and explicit store access (write). This field is set at the semantics level.
        std::set<std::pair<triton::arch::MemoryAccess, triton::ast::AbstractNode*>> storeAccess;

        //! Implicit and explicit register inputs (read). This field is set at the semantics level.
        std::set<std::pair<triton::arch::Register, triton::ast::AbstractNode*>> readRegisters;

        //! Implicit and explicit register outputs (write). This field is set at the semantics level.
        std::set<std::pair<triton::arch::Register, triton::ast::AbstractNode*>> writtenRegisters;

        //! Implicit and explicit immediate inputs (read). This field is set at the semantics level.
        std::set<std::pair<triton::arch::Immediate, triton::ast::AbstractNode*>> readImmediates;

        //! True if this instruction is a branch. This field is set at the disassembly level.
        bool branch;

        //! True if this instruction changes the control flow. This field is set at the disassembly level.
        bool controlFlow;

        //! True if the condition is taken (i.g x86: jcc, cmocc, setcc, ...). This field is set at the semantics level.
        bool conditionTaken;

        //! True if this instruction is tainted. This field is set at the semantics level.
        bool tainted;

    private:
        //! Copies an Instruction
        void copy(const Instruction& other);

      public:
        //! A list of operands
        std::vector<triton::arch::OperandWrapper> operands;

        //! The semantics set of the instruction.
        std::vector<triton::engines::symbolic::SymbolicExpression*> symbolicExpressions;

        //! Constructor.
        TRITON_EXPORT Instruction();

        //! Constructor with opcode.
        TRITON_EXPORT Instruction(const triton::uint8* opcode, triton::uint32 opSize);

        //! Constructor by copy.
        TRITON_EXPORT Instruction(const Instruction& other);

        //! Copies an Instruction.
        TRITON_EXPORT Instruction& operator=(const Instruction& other);

        //! Returns the thread id of the instruction.
        TRITON_EXPORT triton::uint32 getThreadId(void) const;

        //! Sets the thread id of the instruction.
        TRITON_EXPORT void setThreadId(triton::uint32 tid);

        //! Returns the address of the instruction.
        TRITON_EXPORT triton::uint64 getAddress(void) const;

        //! Returns the next address of the instruction.
        TRITON_EXPORT triton::uint64 getNextAddress(void) const;

        //! Sets the address of the instruction.
        TRITON_EXPORT void setAddress(triton::uint64 addr);

        //! Returns the disassembly of the instruction.
        TRITON_EXPORT std::string getDisassembly(void) const;

        //! Returns the opcode of the instruction.
        TRITON_EXPORT const triton::uint8* getOpcode(void) const;

        //! Returns the type of the instruction.
        TRITON_EXPORT triton::uint32 getType(void) const;

        //! Returns the prefix of the instruction.
        TRITON_EXPORT triton::uint32 getPrefix(void) const;

        //! Returns the list of all implicit and explicit load access
        TRITON_EXPORT std::set<std::pair<triton::arch::MemoryAccess, triton::ast::AbstractNode*>>& getLoadAccess(void);

        //! Returns the list of all implicit and explicit store access
        TRITON_EXPORT std::set<std::pair<triton::arch::MemoryAccess, triton::ast::AbstractNode*>>& getStoreAccess(void);

        //! Returns the list of all implicit and explicit register (flags includes) inputs (read)
        TRITON_EXPORT std::set<std::pair<triton::arch::Register, triton::ast::AbstractNode*>>& getReadRegisters(void);

        //! Returns the list of all implicit and explicit register (flags includes) outputs (write)
        TRITON_EXPORT std::set<std::pair<triton::arch::Register, triton::ast::AbstractNode*>>& getWrittenRegisters(void);

        //! Returns the list of all implicit and explicit immediate inputs (read)
        TRITON_EXPORT std::set<std::pair<triton::arch::Immediate, triton::ast::AbstractNode*>>& getReadImmediates(void);

        //! Sets the opcode of the instruction.
        TRITON_EXPORT void setOpcode(const triton::uint8* opcode, triton::uint32 size);

        //! Returns the size of the instruction.
        TRITON_EXPORT triton::uint32 getSize(void) const;

        //! Sets a load access.
        TRITON_EXPORT void setLoadAccess(const triton::arch::MemoryAccess& mem, triton::ast::AbstractNode* node);

        //! Removes a load access.
        TRITON_EXPORT void removeLoadAccess(const triton::arch::MemoryAccess& mem);

        //! Sets a store access.
        TRITON_EXPORT void setStoreAccess(const triton::arch::MemoryAccess& mem, triton::ast::AbstractNode* node);

        //! Removes a store access.
        TRITON_EXPORT void removeStoreAccess(const triton::arch::MemoryAccess& mem);

        //! Sets a read register.
        TRITON_EXPORT void setReadRegister(const triton::arch::Register& reg, triton::ast::AbstractNode* node);

        //! Removes a read register.
        TRITON_EXPORT void removeReadRegister(const triton::arch::Register& reg);

        //! Sets a written register.
        TRITON_EXPORT void setWrittenRegister(const triton::arch::Register& reg, triton::ast::AbstractNode* node);

        //! Removes a written register.
        TRITON_EXPORT void removeWrittenRegister(const triton::arch::Register& reg);

        //! Sets a read immediate.
        TRITON_EXPORT void setReadImmediate(const triton::arch::Immediate& imm, triton::ast::AbstractNode* node);

        //! Removes a read immediate.
        TRITON_EXPORT void removeReadImmediate(const triton::arch::Immediate& imm);

        //! Sets the size of the instruction.
        TRITON_EXPORT void setSize(triton::uint32 size);

        //! Sets the type of the instruction.
        TRITON_EXPORT void setType(triton::uint32 type);

        //! Sets the prefix of the instruction.
        TRITON_EXPORT void setPrefix(triton::uint32 prefix);

        //! Sets the disassembly of the instruction.
        TRITON_EXPORT void setDisassembly(const std::string& str);

        //! Sets the taint of the instruction.
        TRITON_EXPORT void setTaint(bool state);

        //! Sets the taint of the instruction based on its expressions.
        TRITON_EXPORT void setTaint(void);

        //! Adds a symbolic expression
        TRITON_EXPORT void addSymbolicExpression(triton::engines::symbolic::SymbolicExpression* expr);

        //! Returns true if this instruction is a branch
        TRITON_EXPORT bool isBranch(void) const;

        //! Returns true if this instruction changes the control flow (e.g x86: JMP, JCC, CALL, RET, ...)
        TRITON_EXPORT bool isControlFlow(void) const;

        //! Returns true if the condition is taken (e.g x86: jcc, cmovcc, setcc, ...).
        TRITON_EXPORT bool isConditionTaken(void) const;

        //! Returns true if at least one of its expressions is tainted.
        TRITON_EXPORT bool isTainted(void) const;

        //! Returns true if at least one of its expressions contains a symbolic variable.
        TRITON_EXPORT bool isSymbolized(void) const;

        //! Returns true if the instruction contains an expression which reads the memory.
        TRITON_EXPORT bool isMemoryRead(void) const;

        //! Returns true if the instruction contains an expression which writes into the memory.
        TRITON_EXPORT bool isMemoryWrite(void) const;

        //! Returns whether the instruction writes the specified operand.
        TRITON_EXPORT bool isWriteTo(const triton::arch::OperandWrapper& target) const;

        //! Returns whether the instruction reads the specified operand.
        TRITON_EXPORT bool isReadFrom(const triton::arch::OperandWrapper& target) const;

        //! Returns true if the instruction has a prefix.
        TRITON_EXPORT bool isPrefixed(void) const;

        //! Sets flag to define this instruction as branch or not.
        TRITON_EXPORT void setBranch(bool flag);

        //! Sets flag to define this instruction changes the control flow or not.
        TRITON_EXPORT void setControlFlow(bool flag);

        //! Sets flag to define if the condition is taken or not.
        TRITON_EXPORT void setConditionTaken(bool flag);

        //! Resets all instruction information.
        TRITON_EXPORT void reset(void);

        //! Resets partially instruction information. All except memory and register states.
        TRITON_EXPORT void partialReset(void);
    };

    //! Displays an Instruction.
    TRITON_EXPORT std::ostream& operator<<(std::ostream& stream, const Instruction& inst);

    //! Displays an Instruction.
    TRITON_EXPORT std::ostream& operator<<(std::ostream& stream, const Instruction* inst);

  /*! @} End of arch namespace */
  };
/*! @} End of triton namespace */
};

#endif /* TRITON_INSTRUCTION_H */
