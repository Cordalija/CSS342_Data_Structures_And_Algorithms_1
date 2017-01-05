//Jasenko.Cordalija CS 342 P6

// Public routine that performs the evaluation. Examines the postfix machine
// to see if a single result is left and if so, return it; otherwise prints
// error.
template<class NumericType>
NumericType Evaluator<NumericType>::getValue( ) {

  Tokenizer<NumericType> tok( str );
  Token<NumericType> lastToken;
  
  do {
    lastToken = tok.getToken( );
    processToken( lastToken );
  } while ( lastToken.getType( ) != EOL );

  if ( postFixStack.empty( ) ) {
    cerr << "1Missing operatnd!" << endl;
    return 0;
  }

  NumericType theResult = postFixStack.back( );
  postFixStack.pop_back( );
  if ( !postFixStack.empty( ) )
    cerr << "Warning: missing operators!" << endl;
  
  return theResult;
}

// After token is read, use operator precedence parsing algorithm to process
// it; missing opening parentheses are detected here.
template<class NumericType>
void Evaluator<NumericType>::
processToken( const Token<NumericType> &lastToken ) {
  TokenType topOp;
  TokenType lastType = lastToken.getType( );

  switch( lastType ) {
  case VALUE:
    postFixStack.push_back( lastToken.getValue( ) );
    return;
	
	// Handling three variables 'a,b,c'
	// Variable a, handles var a by pushing in stack and 'a' into var stack
  case VAR_A: 
	  postFixStack.push_back(var_a);
	  postFixVarStack.push_back('a');
	  return;

	  // handles Variable b, handles var b by pushing in stack and 'b' into var stack
  case VAR_B:
	  postFixStack.push_back(var_b);
	  postFixVarStack.push_back('b');
	  return;

	  // handles Variable c, handles var c by pushing in stack and 'c' into var stack
  case VAR_C: 
	  postFixStack.push_back(var_c);
	  postFixVarStack.push_back('c');
	  return;
	  

  case CPAREN:
    while( ( topOp = opStack.back( ) ) != OPAREN &&
	   topOp != EOL )
      binaryOp( topOp );
    if ( topOp == OPAREN )
      opStack.pop_back( ); // get rid of opening parethesis
    else
      cerr << "Missing open parenthesis" << endl;
    break;

  default: // general operator case
    while ( PREC_TABLE[ lastType ].inputSymbol <= 
	    PREC_TABLE[ topOp = opStack.back( ) ].topOfStack )
      binaryOp( topOp );

    if ( lastToken.getType( ) != EOL )
      opStack.push_back( lastType );

    break;
  }
}

// Process an operator by taking two items off the postfix stack, applying
// the operator, and pushing the result.
// Print error if missing closing parenthesis or division by 0.
template<class NumericType>
void Evaluator<NumericType>::binaryOp(TokenType topOp) {
	if (topOp == OPAREN) {
		cerr << "Unbalanced parenthss" << endl;
		opStack.pop_back();
		return;
	}

	// Check for, if Uniary Operators '+,-,!,~' else uses binary
	// check if it is any of the unary ones listed above.
	if (topOp == UN_PLUS || topOp == UN_MINUS || topOp == BIT_COMP || topOp == NOT) {

		NumericType lhs = getTop(); // left side is top
		
		if (topOp == UN_PLUS)
			postFixStack.push_back(+lhs); // adds left
		else if (topOp == UN_MINUS)
			postFixStack.push_back(-lhs); // minus left
		else if (topOp == BIT_COMP)
			postFixStack.push_back(~lhs); // bit left
		else if (topOp == NOT)
			postFixStack.push_back(!lhs); // not left
	}

	else {
	
	// Now uses the binary since it is not a uniary
	NumericType rhs = getTop();
	NumericType lhs = getTop(); 

	// Plus through Log or already given so no extra comments needed on these
	if (topOp == PLUS)
		postFixStack.push_back(lhs + rhs);
	else if (topOp == MINUS)
		postFixStack.push_back(lhs - rhs);
	else if (topOp == MULT)
		postFixStack.push_back(lhs * rhs);
	else if (topOp == DIV) {
		if (rhs != 0)
			postFixStack.push_back(lhs / rhs);
		else {
			cerr << "Division by zero" << endl;
			postFixStack.push_back(lhs);
		}
	}

	else if (topOp == MODULUS)
		postFixStack.push_back(lhs % rhs);
	else if (topOp == SHIFT_L)
		postFixStack.push_back(lhs << rhs);
	else if (topOp == SHIFT_R)
		postFixStack.push_back(lhs >> rhs);
	else if (topOp == LT)
		postFixStack.push_back(lhs < rhs);
	else if (topOp == LE)
		postFixStack.push_back(lhs <= rhs);
	else if (topOp == GT)
		postFixStack.push_back(lhs > rhs);
	else if (topOp == GE)
		postFixStack.push_back(lhs >= rhs);
	else if (topOp == EQUAL)
		postFixStack.push_back(lhs == rhs);
	else if (topOp == NOTEQUAL)
		postFixStack.push_back(lhs != rhs);
	else if (topOp == BIT_AND)
		postFixStack.push_back(lhs & rhs);
	else if (topOp == BIT_EOR)
		postFixStack.push_back(lhs ^ rhs);
	else if (topOp == BIT_IOR)
		postFixStack.push_back(lhs | rhs);
	else if (topOp == LOG_AND)
		postFixStack.push_back(lhs && rhs);
	else if (topOp == LOG_OR)
		postFixStack.push_back(lhs || rhs);

	// Assignment Operator '='
	else if (topOp == ASSIGN) { // ASSIGN is '='
		char cch = postFixVarStack.back(); // cch is back fix var stack
		switch (cch) { 			// runs for a,b,c & break if one of cases
		case 'a': var_a = rhs;
			break;
		case 'b': var_b = rhs;
			break;
		case 'c': var_c = rhs;
			break;
		}
		postFixStack.push_back(lhs = rhs); //  pushes back the right side to equal left
		postFixVarStack.push_back(cch);		// pushes back also in var stack too
	}
}
  opStack.pop_back( );	// must pop back from stack afterwards

}

// top and pop the postfix machine stack; return the result.
// If the stack is empty, print an error message.
template<class NumericType>
NumericType Evaluator<NumericType>::getTop( ) {
  if ( postFixStack.empty( ) ) {
    cerr << "Missing operand" << endl;
    return 0;
  }

  NumericType tmp = postFixStack.back( );
  postFixStack.pop_back( );
  return tmp;
}
