// status

#define FOREACH_STAT(STAT) \
  STAT(INITIAL)            \
  STAT(WHITE_SPACE)        \
  STAT(CR)                 \
  STAT(LF)                 \
  STAT(NEWLINE)            \
  STAT(SINGLEQUOTE)        \
  STAT(DOUBLEQUOTE)        \
  STAT(STRING)             \
  STAT(NUMBER)             \
  STAT(IDENT)              \
  STAT(PUNCT)              \
  STAT(PUNCT_WAITEQ)       \
  STAT(PUNCT_EQSTART)      \
  STAT(PUNCT_REPEAT)       \
  STAT(_NULL)              \
  STAT(_TRUE)              \
  STAT(_FALSE)             \
  STAT(AWAIT)              \
  STAT(BREAK)              \
  STAT(CASE)               \
  STAT(CATCH)              \
  STAT(CLASS)              \
  STAT(CONST)              \
  STAT(CONTINUE)           \
  STAT(DEBUGGER)           \
  STAT(DEFAULT)            \
  STAT(DELETE)             \
  STAT(DO)                 \
  STAT(ELSE)               \
  STAT(ENUM)               \
  STAT(EXPORT)             \
  STAT(EXTENDS)            \
  STAT(FINALLY)            \
  STAT(FOR)                \
  STAT(FUNCTION)           \
  STAT(IF)                 \
  STAT(IMPORT)             \
  STAT(IN)                 \
  STAT(INSTANCEOF)         \
  STAT(NEW)                \
  STAT(RETURN)             \
  STAT(SUPER)              \
  STAT(SWITCH)             \
  STAT(THIS)               \
  STAT(THROW)              \
  STAT(TRY)                \
  STAT(TYPEOF)             \
  STAT(VAR)                \
  STAT(VOID)               \
  STAT(WHILE)              \
  STAT(WITH)               \
  STAT(YIELD)              \
  STAT(LBRACE)             \
  STAT(LPAREN)             \
  STAT(RPAREN)             \
  STAT(LBRACK)             \
  STAT(RBRACK)             \
  STAT(DOT)                \
  STAT(DOT3)               \
  STAT(SEMI)               \
  STAT(COMMA)              \
  STAT(LT)                 \
  STAT(GT)                 \
  STAT(LTEQ)               \
  STAT(GTEQ)               \
  STAT(EQ2)                \
  STAT(NOTEQ)              \
  STAT(EQ3)                \
  STAT(NOTEQ2)             \
  STAT(PLUS)               \
  STAT(MINUS)              \
  STAT(STAR)               \
  STAT(PERCENT)            \
  STAT(STAR2)              \
  STAT(PLUS2)              \
  STAT(MINUS2)             \
  STAT(LSHIFT)             \
  STAT(RSHIFT)             \
  STAT(GT3)                \
  STAT(AMPER)              \
  STAT(PIPE)               \
  STAT(CAROT)              \
  STAT(EXCLAMATION)        \
  STAT(TILDE)              \
  STAT(AMPER2)             \
  STAT(PIPE2)              \
  STAT(QUESTION2)          \
  STAT(QUESTION)           \
  STAT(COLON)              \
  STAT(EQ)                 \
  STAT(PLUSEQ)             \
  STAT(MINUSEQ)            \
  STAT(TIMESEQ)            \
  STAT(PERCENTEQ)          \
  STAT(TIME2SEQ)           \
  STAT(LSHIFTEQ)           \
  STAT(RSHIFTEQ)           \
  STAT(GT3EQ)              \
  STAT(AMPEREQ)            \
  STAT(PIPEEQ)             \
  STAT(CAROTEQ)            \
  STAT(ARROW)              \
  STAT(DIV)                \
  STAT(DIVEQ)              \
  STAT(RBRACE)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,
#define LJS(content) __LJS_##content

#define __LJS_TAB ('\t')
#define __LJS_SP (' ')
#define __LJS_DOLLAR ('$')
#define __LJS_UNDERSCORE ('_')
#define __LJS_CR ('\r')
#define __LJS_LF ('\n')
#define __LJS_SINGLEQUOTE ('\'')
#define __LJS_DOUBLEQUOTE ('"')

#define __LJS_LBRACE ("{")
#define __LJS_LPAREN ("(")
#define __LJS_RPAREN (")")
#define __LJS_LBRACK ("[")
#define __LJS_RBRACK ("]")
#define __LJS_DOT (".")
#define __LJS_DOT3 ("...")
#define __LJS_SEMI (";")
#define __LJS_COMMA (",")
#define __LJS_LT ("<")
#define __LJS_GT (">")
#define __LJS_LTEQ ("<=")
#define __LJS_GTEQ (">=")
#define __LJS_EQ2 ("==")
#define __LJS_NOTEQ ("!=")
#define __LJS_EQ3 ("===")
#define __LJS_NOTEQ2 ("!==")
#define __LJS_PLUS ("+")
#define __LJS_MINUS ("-")
#define __LJS_STAR ("*")
#define __LJS_PERCENT ("%")
#define __LJS_STAR2 ("**")
#define __LJS_PLUS2 ("++")
#define __LJS_MINUS2 ("--")
#define __LJS_LSHIFT ("<<")
#define __LJS_RSHIFT (">>")
#define __LJS_GT3 (">>>")
#define __LJS_AMPER ("&")
#define __LJS_PIPE ("|")
#define __LJS_CAROT ("^")
#define __LJS_EXCLAMATION ("!")
#define __LJS_TILDE ("~")
#define __LJS_AMPER2 ("&&")
#define __LJS_PIPE2 ("||")
#define __LJS_QUESTION2 ("??")
#define __LJS_QUESTION ("?")
#define __LJS_COLON (":")
#define __LJS_EQ ("=")
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
#define __LJS_RBRACE ("}")

#define __LJS_e ('e')
#define __LJS_E ('E')
#define __LJS_BIGINTSUFFIX ('n')
#define __LJS_NONDECIMALPREFIX ('0')

#define NEXTCHAR                \
  {                             \
    content[content_pos++] = c; \
    continue;                   \
  }
#define SETSTAT(STAT) \
  {                   \
    status = STAT;    \
    continue;         \
  }

const char *__LJS_PUNCTUATOR_SINGLE_CHARS = "{([])};,~:";
const char *__LJS_PUNCTUATOR_WAITEQ_CHARS = "!%^/";
const char *__LJS_PUNCTUATOR_EQSTART_CHARS = "=";
const char *__LJS_PUNCTUATOR_REPEAT_CHARS = ".<>+-*&|?";
const char *__LJS_PUNCTUATOR_CHARS = "{([])}.;,<>=!+-*%&|^~?:/";
const char *__LJS_NON_DECIMAL_CHARS = "bBoOxX";

enum STAT_ENUM
{
  FOREACH_STAT(GENERATE_ENUM)
};
const char *STAT_STRING[] = {FOREACH_STAT(GENERATE_STRING)};

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
