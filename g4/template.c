#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <uchar.h>
#include <memory.h>

// char a[] = u8"\u000b";
// char b[] = u8"\u000c";

// status
enum
{
  INITIAL,
  WHITE_SPACE,
  IDENTIFIER,
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
  YIELD
};

char source_code[1024];

#define LJS(content) __LJS_##content
#define __LJS_TAB ('\t')
#define __LJS_SP (' ')
#define __LJS_DOLLAR ('$')
#define __LJS_UNDERSCORE ('_')
// #define __LJS_VT (u8"\u000b")
// #define __LJS_FF (u8"\u000c")
// #define __LJS_SP (u8"\u0020")
// #define __LJS_NBSP (u8"\u00a0")
// #define __LJS_ZWNBSP (u8"\u2060")
// #define __LJS_USP (u8"\u0009")

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

int status;
int token_loc;
char content[100];
int content_loc;
char c;

__LJS_NT_Return *finish(int new_pos);

void init()
{
  token_loc = 0;
  content_loc = 0;
  int i = 0;
  for (i = 0; i < 100; i++)
  {
    content[i] = 0;
  }
  status = INITIAL;
}

int is_letter(char c)
{
  if (c >= 'a' && c <= 'z')
  {
    return 1;
  }
  else if (c >= 'A' && c <= 'Z')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int is_digit(char c)
{
  return c >= '0' && c <= '9';
}

int is_identifier_start(char c)
{
  if (c == LJS(DOLLAR) || c == LJS(UNDERSCORE) || is_letter(c))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int is_identifier_part(char c)
{
  if (is_identifier_start(c))
  {
    return 1;
  }
  else if (is_digit(c))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

__LJS_NT_Return *identifier_finish(int pos)
{
  // printf("content = %s\n", content);
  if (strcmp(content, "await") == 0)
  {
    status = AWAIT;
  }
  else if (strcmp(content, "break") == 0)
  {
    status = BREAK;
  }
  else if (strcmp(content, "case") == 0)
  {
    status = CASE;
  }
  else if (strcmp(content, "catch") == 0)
  {
    status = CATCH;
  }
  else if (strcmp(content, "class") == 0)
  {
    status = CLASS;
  }
  else if (strcmp(content, "const") == 0)
  {
    status = CONST;
  }
  else if (strcmp(content, "continue") == 0)
  {
    status = CONTINUE;
  }
  else if (strcmp(content, "debugger") == 0)
  {
    status = DEBUGGER;
  }
  else if (strcmp(content, "default") == 0)
  {
    status = DEFAULT;
  }
  else if (strcmp(content, "delete") == 0)
  {
    status = DELETE;
  }
  else if (strcmp(content, "do") == 0)
  {
    status = DO;
  }
  else if (strcmp(content, "else") == 0)
  {
    status = ELSE;
  }
  else if (strcmp(content, "enum") == 0)
  {
    status = ENUM;
  }
  else if (strcmp(content, "export") == 0)
  {
    status = EXPORT;
  }
  else if (strcmp(content, "extends") == 0)
  {
    status = EXTENDS;
  }
  else if (strcmp(content, "false") == 0)
  {
    status = FALSE;
  }
  else if (strcmp(content, "finally") == 0)
  {
    status = FINALLY;
  }
  else if (strcmp(content, "for") == 0)
  {
    status = FOR;
  }
  else if (strcmp(content, "function") == 0)
  {
    status = FUNCTION;
  }
  else if (strcmp(content, "if") == 0)
  {
    status = IF;
  }
  else if (strcmp(content, "import") == 0)
  {
    status = IMPORT;
  }
  else if (strcmp(content, "in") == 0)
  {
    status = IN;
  }
  else if (strcmp(content, "instanceof") == 0)
  {
    status = INSTANCEOF;
  }
  else if (strcmp(content, "new") == 0)
  {
    status = NEW;
  }
  else if (strcmp(content, "null") == 0)
  {
    status = _NULL;
  }
  else if (strcmp(content, "return") == 0)
  {
    status = RETURN;
  }
  else if (strcmp(content, "super") == 0)
  {
    status = SUPER;
  }
  else if (strcmp(content, "switch") == 0)
  {
    status = SWITCH;
  }
  else if (strcmp(content, "this") == 0)
  {
    status = THIS;
  }
  else if (strcmp(content, "throw") == 0)
  {
    status = THROW;
  }
  else if (strcmp(content, "true") == 0)
  {
    status = TRUE;
  }
  else if (strcmp(content, "try") == 0)
  {
    status = TRY;
  }
  else if (strcmp(content, "typeof") == 0)
  {
    status = TYPEOF;
  }
  else if (strcmp(content, "var") == 0)
  {
    status = VAR;
  }
  else if (strcmp(content, "void") == 0)
  {
    status = VOID;
  }
  else if (strcmp(content, "while") == 0)
  {
    status = WHILE;
  }
  else if (strcmp(content, "with") == 0)
  {
    status = WITH;
  }
  else if (strcmp(content, "yield") == 0)
  {
    status = YIELD;
  }
  return finish(pos);
}

char get_char(int position)
{
  return source_code[position];
}

__LJS_NT_Return *next_token(int position)
{
  init();
  int pos = position;
  // printf("%d\n", content_loc);
  while (1)
  {
    switch (status)
    {
    case INITIAL:
      c = get_char(pos++);
      content[content_loc++] = c;
      // printf("c = %c\n", c);
      if (c == LJS(TAB) || c == LJS(SP))
      {
        status = WHITE_SPACE;
        continue;
      }
      else if (is_identifier_start(c))
      {
        status = IDENTIFIER;
        continue;
      }
      break;
    case IDENTIFIER:
      c = get_char(pos++);
      // printf("identifier: %c\n", c);
      if (is_identifier_part(c))
      {
        content[content_loc++] = c;
        continue;
      }
      else
      {
        return identifier_finish(--pos);
      }
      break;
    case WHITE_SPACE:
      return finish(pos);
    }
  }
}

__LJS_NT_Return *finish(int new_pos)
{
  Token *token = (Token *)malloc(sizeof(Token));
  sprintf(token->content, "%s", content);
  token->type = status;
  __LJS_NT_Return *res = (__LJS_NT_Return *)malloc(sizeof(__LJS_NT_Return));
  res->token = token;
  res->position = new_pos;
  return res;
}

char *translate(int value)
{
  switch (value)
  {
  case WHITE_SPACE:
    return "WHITE_SPACE";
  case AWAIT:
    return "AWAIT";
  case BREAK:
    return "BREAK";
  case IDENTIFIER:
    return "IDENTIFIER";
  default:
    return "TYPE!";
  }
}

int main()
{

  FILE *fp = fopen("white.js.txt", "r");
  fgets(source_code, 1024, (FILE *)fp);

  int position = 0;
  int len = strlen(source_code);
  while (position < len)
  {
    __LJS_NT_Return *res = next_token(position);
    position = res->position;
    // printf("position: %d\n", position);
    printf("%s\n", translate(res->token->type));
  }

  fclose(fp);
  return 0;
}
