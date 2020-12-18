#include <Common.h>

#include <cassert>
#include <memory>
#include <string>

enum class Token : int {
  Multiply = '*',
  Plus = '+',
  LParens = '(',
  RParens = ')',
  Number = 1,
  Eof = -1,
};

class Lexer {
public:
  /// Token consumes a buffer of input
  Lexer(const std::string &buffer) : buffer(buffer){};

  /// Look at the current token in the stream.
  Token getCurToken() { return curTok; }

  /// Move to the next token in the stream and return it.
  Token getNextToken() { return curTok = getTok(); }

  /// Move to the next token in the stream and return it.
  long getNumVal() { return numVal; }

  /// Consume a token from the input
  void match(Token tok) {
    if (tok != curTok)
      assert(tok == curTok && "Token mismatch");
    getNextToken();
  }

private:
  /// Get the next character from the input stream
  int getNextChar() {
    if (idx == buffer.size())
      return EOF;

    return buffer[idx++];
  }

  /// Get the next token from the stream
  Token getTok() {
    // ignore whitespace
    while (isspace(curChar))
      curChar = getNextChar();

    if (isdigit(curChar)) {
      std::string numStr;
      do {
        numStr += static_cast<char>(curChar);
        curChar = getNextChar();
      } while (isdigit(curChar));

      numVal = std::stol(numStr);
      return Token::Number;
    }

    if (curChar == EOF)
      return Token::Eof;

    Token thisChar = Token(curChar);
    curChar = getNextChar();
    return thisChar;
  }

  /// Number matched from input
  long numVal;

  /// Current token lookahead
  Token curTok;

  /// Last character read from the string buffer
  int curChar = ' ';

  /// Current location in the string buffer
  std::size_t idx = 0;

  const std::string buffer = "";
};

class ParserP2 {
public:
  ParserP2(Lexer &lexer) : lexer(lexer) {}

  /// S := expr $
  long parseExpression() {
    /// Prime the lexer at the beginning
    lexer.getNextToken();

    return parseExpr();
  }

private:
  /// expr  := factor expr'
  /// expr' := '*' factor expr' |
  ///       := ε
  long parseExpr() {
    long result = parseFactor();

    while (lexer.getCurToken() == Token::Multiply) {
      if (lexer.getCurToken() == Token::Multiply) {
        lexer.match(Token::Multiply);
        result *= parseFactor();
      }
    }

    return result;
  }

  /// factor  := term factor'
  /// factor' := '+' term factor' |
  ///         := ε
  long parseFactor() {
    long result = parseTerm();

    while (lexer.getCurToken() == Token::Plus) {
      if (lexer.getCurToken() == Token::Plus) {
        lexer.match(Token::Plus);
        result += parseTerm();
      }
    }

    return result;
  }

  /// term  := '(' expr ')' |
  ///       := <num>
  long parseTerm() {
    long result;
    if (lexer.getCurToken() == Token::LParens) {
      lexer.match(Token::LParens);
      result = parseExpr();
      lexer.match(Token::RParens);
    } else {
      lexer.match(Token::Number);
      result = lexer.getNumVal();
    }

    return result;
  }

  Lexer &lexer;
};

class ParserP1 {
public:
  ParserP1(Lexer &lexer) : lexer(lexer) {}

  /// S := expr $
  long parseExpression() {
    /// Prime the lexer at the beginning
    lexer.getNextToken();

    return parseExpr();
  }

private:
  /// expr  := factor expr'
  /// expr' := '+' factor expr' |
  ///       := '*' factor expr' |
  ///       := factor
  long parseExpr() {
    long result = parseTerm();

    while (lexer.getCurToken() == Token::Plus ||
           lexer.getCurToken() == Token::Multiply) {
      if (lexer.getCurToken() == Token::Plus) {
        lexer.match(Token::Plus);
        result += parseTerm();
      } else if (lexer.getCurToken() == Token::Multiply) {
        lexer.match(Token::Multiply);
        result *= parseTerm();
      }
    }

    return result;
  }

  /// term  := '(' expr ')' |
  ///       := <num>
  long parseTerm() {
    long result;
    if (lexer.getCurToken() == Token::LParens) {
      lexer.match(Token::LParens);
      result = parseExpr();
      lexer.match(Token::RParens);
    } else {
      lexer.match(Token::Number);
      result = lexer.getNumVal();
    }

    return result;
  }

  Lexer &lexer;
};

/// Over-engineered parser
int main() {
  auto lines = getLines(getFileContents("../input/Day18/input.txt"));
  long s1 = 0;
  long s2 = 0;
  for (const auto &line : lines) {
    Lexer l1(line);
    Lexer l2(line);
    ParserP1 p1(l1);
    ParserP2 p2(l2);
    s1 += p1.parseExpression();
    s2 += p2.parseExpression();
  }

  std::cout << s1 << "\n";
  std::cout << s2 << "\n";
}
