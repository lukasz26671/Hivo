#include "AST.h"
#include "Utils.h"
#include "global.h"

namespace Hivo {

	AST::AST(int type) {
		
		this->type = AstTypeCast(type);
	}
	AST::~AST() {}

}