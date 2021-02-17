//
// Created by rex on 2020/7/26.
//

#include "rtti.h"

namespace rexlang {

    const char * rtti::name(NodeType nodeType) {
        switch (nodeType) {
            if (0) { case NodeType::kNTyBadType:             return nullptr;               }
            if (0) { case NodeType::kNTySourceFile:          return "SourceFile";          }
            if (0) { case NodeType::kNTyProgramSetFile:      return "ProgramSetFile";      }
            if (0) { case NodeType::kNTyGlobalVariableFile:  return "GlobalVariableFile";  }
            if (0) { case NodeType::kNTyDataStructureFile:   return "DataStructureFile";   }
            if (0) { case NodeType::kNTyAPIDeclareFile:      return "APIDeclareFile";      }
            if (0) { case NodeType::kNTyMacroDeclareFile:    return "MacroDeclareFile";    }
            if (0) { case NodeType::kNTyIdentDef:            return "IdentDef";            }
            if (0) { case NodeType::kNTyDecl:                return "Decl";                }
            if (0) { case NodeType::kNTyTagDecl:             return "TagDecl";             }
            if (0) { case NodeType::kNTyBaseVariDecl:        return "BaseVariDecl";        }
            if (0) { case NodeType::kNTyParameterDecl:       return "ParameterDecl";       }
            if (0) { case NodeType::kNTyMacroDecl:           return "MacroDecl";           }
            if (0) { case NodeType::kNTyVariableDecl:        return "VariableDecl";        }
            if (0) { case NodeType::kNTyGlobalVariableDecl:  return "GlobalVariableDecl";  }
            if (0) { case NodeType::kNTyMemberVariableDecl:  return "MemberVariableDecl";  }
            if (0) { case NodeType::kNTyFileVariableDecl:    return "FileVariableDecl";    }
            if (0) { case NodeType::kNTyLocalVariableDecl:   return "LocalVariableDecl";   }
            if (0) { case NodeType::kNTyTypeDecl:            return "TypeDecl";            }
            if (0) { case NodeType::kNTyVariTypeDecl:        return "VariTypeDecl";        }
            if (0) { case NodeType::kNTyReferenceType:       return "ReferenceType";       }
            if (0) { case NodeType::kNTyBuiltinType:         return "BuiltinType";     }
            if (0) { case NodeType::kNTyStructureDecl:       return "StructureDecl";       }
            if (0) { case NodeType::kNTyArrayType:           return "ArrayType";           }
            if (0) { case NodeType::kNTyFunctorDecl:         return "FunctorDecl";         }
            if (0) { case NodeType::kNTyFunctionDecl:        return "FunctionDecl";        }
            if (0) { case NodeType::kNTyAPICommandDecl:      return "APICommandDecl";      }
            if (0) { case NodeType::kNTyProgSetDecl:         return "ProgSetDecl";         }
            if (0) { case NodeType::kNTyStatement:           return "Statement";           }
            if (0) { case NodeType::kNTyAssignStmt:          return "AssignStmt";          }
            if (0) { case NodeType::kNTyControlStmt:         return "ControlStmt";         }
            if (0) { case NodeType::kNTyLoopControlStmt:     return "LoopControlStmt";     }
            if (0) { case NodeType::kNTyContinueStmt:        return "ContinueStmt";        }
            if (0) { case NodeType::kNTyBreakStmt:           return "BreakStmt";           }
            if (0) { case NodeType::kNTyReturnStmt:          return "ReturnStmt";          }
            if (0) { case NodeType::kNTyExitStmt:            return "ExitStmt";            }
            if (0) { case NodeType::kNTyIfStmt:              return "IfStmt";              }
            if (0) { case NodeType::kNTyWhileStmt:           return "WhileStmt";           }
            if (0) { case NodeType::kNTyRangeForStmt:        return "RangeForStmt";        }
            if (0) { case NodeType::kNTyForStmt:             return "ForStmt";             }
            if (0) { case NodeType::kNTyDoWhileStmt:         return "DoWhileStmt";         }
            if (0) { case NodeType::kNTyStatementBlock:      return "StatementBlock";      }
            if (0) { case NodeType::kNTyExpression:          return "Expression";          }
            if (0) { case NodeType::kNTyNameComponent:       return "NameComponent";       }
            if (0) { case NodeType::kNTyIdentRefer:          return "IdentRefer";          }
            if (0) { case NodeType::kNTyArrayIndex:          return "ArrayIndex";          }
            if (0) { case NodeType::kNTyFunctionCall:        return "FunctionCall";        }
            if (0) { case NodeType::kNTyTypeConvert:         return "TypeConvert";         }
            if (0) { case NodeType::kNTyOperatorExpression:  return "OperatorExpression";  }
            if (0) { case NodeType::kNTyUnaryExpression:     return "UnaryExpression";     }
            if (0) { case NodeType::kNTyBinaryExpression:    return "BinaryExpression";    }
            if (0) { case NodeType::kNTyValue:               return "Value";               }
            if (0) { case NodeType::kNTyValueOfDataSet:      return "ValueOfDataSet";      }
            if (0) { case NodeType::kNTyValueOfDatetime:     return "ValueOfDatetime";     }
            if (0) { case NodeType::kNTyFuncAddrExpression:  return "FuncAddrExpression";  }
            if (0) { case NodeType::kNTyValueOfBool:         return "ValueOfBool";         }
            if (0) { case NodeType::kNTyValueOfDecimal:      return "ValueOfDecimal";      }
            if (0) { case NodeType::kNTyValueOfString:       return "ValueOfString";       }
            if (0) { case NodeType::kNTyTranslateUnit:       return "TranslateUnit";       }
        }
        assert(false);
        return nullptr;
    }

}
