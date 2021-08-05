// status
enum
{
  INITIAL,
  WHITE_SPACE,
  IDENTIFIER,
  PUNCTUATOR,
  AWAIT,
  BREAK,
  CASE,
  CATCH,
  CLASS,
  CONST,
  CONTINUE,
  DEBUGGER,
  DEFAULT,
  DELETE,
  DO,
  ELSE,
  ENUM,
  EXPORT,
  EXTENDS,
  FALSE,
  FINALLY,
  FOR,
  FUNCTION,
  IF,
  IMPORT,
  IN,
  INSTANCEOF,
  NEW,
  _NULL,
  RETURN,
  SUPER,
  SWITCH,
  THIS,
  THROW,
  TRUE,
  TRY,
  TYPEOF,
  VAR,
  VOID,
  WHILE,
  WITH,
  YIELD,
  LBRACE,
  LBRACK,
  RBRACK,
  LBRACKET,
  RBRACKET,
  DOT,
  DOT3,
  SEMI,
  COMMA,
  LT,
  GT,
  LTEQ,
  GTEQ,
  EQ2,
  NOTEQ,
  EQ3,
  NOTEQ2,
  PLUS,
  MINUS,
  STAR,
  PERCENT,
  STAR2,
  PLUS2,
  MINUS2,
  LSHIFT,
  RSHIFT,
  GT3,
  AMPER,
  PIPE,
  CAROT,
  EXCLAMATION,
  TILDE,
  AMPER2,
  PIPE2,
  QUESTION2,
  QUESTION,
  COLON,
  EQ,
  PLUSEQ,
  MINUSEQ,
  TIMESEQ,
  PERCENTEQ,
  TIME2SEQ,
  LSHIFTEQ,
  RSHIFTEQ,
  GT3EQ,
  AMPEREQ,
  PIPEEQ,
  CAROTEQ,
  ARROW
};

#define LJS(content) __LJS_##content
#define __LJS_TAB ('\t')
#define __LJS_SP (' ')
#define __LJS_DOLLAR ('$')
#define __LJS_UNDERSCORE ('_')

#define __LJS_LBRACE ('{')
#define __LJS_LBRACK ('(')
#define __LJS_RBRACK (')')
#define __LJS_LBRACKET ('[')
#define __LJS_RBRACKET (']')
#define __LJS_DOT ('.')
#define __LJS_DOT3 ("...")
#define __LJS_SEMI (';')
#define __LJS_COMMA (',')
#define __LJS_LT ('<')
#define __LJS_GT ('>')
#define __LJS_LTEQ ("<=")
#define __LJS_GTEQ (">=")
#define __LJS_EQ2 ("==")
#define __LJS_NOTEQ ("!=")
#define __LJS_EQ3 ("===")
#define __LJS_NOTEQ2 ("!==")
#define __LJS_PLUS ('+')
#define __LJS_MINUS ('-')
#define __LJS_STAR ('*')
#define __LJS_PERCENT ('%')
#define __LJS_STAR2 ("**")
#define __LJS_PLUS2 ("++")
#define __LJS_MINUS2 ("--")
#define __LJS_LSHIFT ("<<")
#define __LJS_RSHIFT (">>")
#define __LJS_GT3 (">>>")
#define __LJS_AMPER ('&')
#define __LJS_PIPE ('|')
#define __LJS_CAROT ('^')
#define __LJS_EXCLAMATION ('!')
#define __LJS_TILDE ('~')
#define __LJS_AMPER2 ("&&")
#define __LJS_PIPE2 ("||")
#define __LJS_QUESTION2 ("??")
#define __LJS_QUESTION ('?')
#define __LJS_COLON (':')
#define __LJS_EQ ('=')
#define __LJS_PLUSEQ ("+=")
#define __LJS_MINUSEQ ("-=")
#define __LJS_TIMESEQ ("*=")
#define __LJS_PERCENTEQ ("%=")
#define __LJS_TIME2SEQ ("**=")
#define __LJS_LSHIFTEQ ("<<=")
#define __LJS_RSHIFTEQ (">>=")
#define __LJS_GT3EQ (">>>=")
#define __LJS_AMPEREQ ("&=")
#define __LJS_PIPEEQ ("|=")
#define __LJS_CAROTEQ ("^=")
#define __LJS_ARROW ("=>")

#define __LJS_DIV ("/")
#define __LJS_DIVEQ ("/=")
#define __LJS_RBRACE ('}')

char *__LJS_PUNCTUATOR_CHARS = "{([])}.;,<>=!+-*%&|^~?:/";

typedef struct token
{
  int type;
  char content[100];
} Token;

typedef struct
{
  Token *token;
  int position;
} __LJS_NT_Return;
