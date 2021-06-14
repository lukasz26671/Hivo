#include "includes/AST.h"
#include "includes/Utils.h"
#include "includes/global.h"

namespace Hivo {

	AST::AST(int type) {
		
		this->type = AstTypeCast(type);
	}
	AST::~AST() {}

}