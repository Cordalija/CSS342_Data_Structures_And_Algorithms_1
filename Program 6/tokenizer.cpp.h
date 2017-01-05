// Jasenko.Cordalija CS 342 P6

template <class NumericType>
bool Tokenizer<NumericType>::getChar(char &ch) {
	char tmp;

	// skip blanks
	while (in.get(tmp) && tmp == ' ');

	// read a char 
	if (in.good() && tmp != '\n'&& tmp != '\0') {
		ch = tmp;
		return true; // if it is not a delimiter
	}
	else
		return false; // if it's a delimitter
}

template <class NumericType>
Token<NumericType> Tokenizer<NumericType>::getToken() {

	char ch;
	NumericType theValue;
	
	// Assumption was that I only needed to comment code I wrote, which is what I did here
	if (getChar(ch) == true) {
		switch (ch) {
		case '(': return (prevToken = OPAREN);
		case ')': return (prevToken = CPAREN);

		// Unary '!' or '!='
		case '!':
			if (getChar(ch) == true && ch == '=')
				return (prevToken = NOTEQUAL); // '!=' since = infront
			in.putback(ch);
			return (prevToken = NOT); // no '=' so case stays '!' (NOT)


		case '*': return (prevToken = MULT);

		case '/': return (prevToken = DIV);

		case '%': return (prevToken = MODULUS);

		// Deciding if Uniary or Binary 
		// Binary or Unary '+' 
		case '+':
			if(prevToken == OPAREN) // if the previous was a ( then it is a unary plus
				return (prevToken = UN_PLUS);
			else
				return (prevToken = PLUS); // else if previous was not a OPAREN then its binary plus


		// Deciding on Binary or Unary '-'
		case '-':
			if (prevToken == OPAREN) // if the previous was a ( then it is a unary minus
				return (prevToken = UN_MINUS);
			else
				return (prevToken = MINUS); // else if previous was not a OPAREN then its binary minus


		// returns Unary '~' operation
		case '~':
			return (prevToken = BIT_COMP); // BIT_COMP is '~'

		case '<':
			if (getChar(ch) == true) {
				switch (ch) {
				case '<': return (prevToken = SHIFT_L);
				case '=': return (prevToken = LE);
				default:
					in.putback(ch);
					return (prevToken = LT);
				}
			}
			in.putback(ch);
			return (prevToken = LT);

		case '>':
			if (getChar(ch) == true) {
				switch (ch) {
				case '>': return (prevToken = SHIFT_R);
				case '=': return (prevToken = GE);
				default:
					in.putback(ch);
					return (prevToken = GT);
				}
			}
			in.putback(ch);
			return (prevToken = GT);

		case '&':
			if (getChar(ch) == true && ch == '&')
				return (prevToken = LOG_AND);
			in.putback(ch);
			return (prevToken = BIT_AND);

		case '^': return (prevToken = BIT_EOR);

		case '|':
			if (getChar(ch) == true && ch == '|')
				return (prevToken = LOG_OR);
			in.putback(ch);
			return (prevToken = BIT_IOR);

		// ASSIGN operator
		case '=':
			if (getChar(ch) == true && ch == '=')
				return (prevToken = EQUAL); // if next is also '=' then Equals 
			in.putback(ch);
			return (prevToken = ASSIGN); // if there is only '=', becomes ASSIGN and assigns one to other.


		// Part for Handling the three variables 'a,b,c'
		// Variable 'a' handling
		case 'a':
			prevToken = VAR_A;
			return Token<NumericType>(VAR_A, 0); // returns  Token with NumericType for var a

			//Variable 'b'
		case 'b':
			prevToken = VAR_B;
			return Token<NumericType>(VAR_B, 0); // returns  Token with NumericType for var b

			//Variable 'c'
		case 'c':
			prevToken = VAR_C;
			return Token<NumericType>(VAR_C, 0); // returns  Token with NumericType for var c


		default:
			in.putback(ch);
			if (!(in >> theValue)) {
				cerr << "Parse error" << endl;
				return (prevToken = EOL);
			}
			prevToken = VALUE;
			return Token<NumericType>(VALUE, theValue);
		}
	}

	return (prevToken = EOL);
}
