#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <uchar.h>
#include <memory.h>
#include "template.h"

char source_code[1024];

int status;
int token_loc;
char content[100];
int content_loc;
char c;

char get_char(int position)
{
  return source_code[position];
}

const char *translate(int value)
{
  return STAT_STRING[value];
}

void nt_init()
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

void nt_error(int pos)
{
  printf("SYNTAX ERROR as %d\n", pos);
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

int is_punctuator_part(char c)
{
  const char *charset = LJS(PUNCTUATOR_CHARS);
  for (int i = 0; i < strlen(charset); ++i)
    if (c == charset[i])
      return 1;
  return 0;
}

int is_punctuator_single(char c)
{
  const char *charset = LJS(PUNCTUATOR_SINGLE_CHARS);
  for (int i = 0; i < strlen(charset); ++i)
    if (c == charset[i])
      return 1;
  return 0;
}

__LJS_NT_Return *identifier_finish(int pos);
__LJS_NT_Return *punctuator_finish(int pos);
__LJS_NT_Return *next_token(int position);
__LJS_NT_Return *finish(int new_pos);

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
    if (res->token->type == WHITE_SPACE)
      continue;
    printf("[%2d]%6s: '%s'\n", position, translate(res->token->type), res->token->content);
  }

  fclose(fp);
  return 0;
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
  else
  {
    status = IDENT;
  }
  return finish(pos);
}

__LJS_NT_Return *punctuator_finish(int pos)
{
  // printf("content = %s\n", content);
  if (strcmp(content, LJS(LBRACE)) == 0)
    status = LBRACE;
  else if (strcmp(content, LJS(LBRACK)) == 0)
  {
    status = LBRACK;
  }
  else if (strcmp(content, LJS(RBRACK)) == 0)
  {
    status = RBRACK;
  }
  else if (strcmp(content, LJS(LBRACKET)) == 0)
  {
    status = LBRACKET;
  }
  else if (strcmp(content, LJS(RBRACKET)) == 0)
  {
    status = RBRACKET;
  }
  else if (strcmp(content, LJS(DOT)) == 0)
  {
    status = DOT;
  }
  else if (strcmp(content, LJS(DOT3)) == 0)
  {
    status = DOT3;
  }
  else if (strcmp(content, LJS(SEMI)) == 0)
  {
    status = SEMI;
  }
  else if (strcmp(content, LJS(COMMA)) == 0)
  {
    status = COMMA;
  }
  else if (strcmp(content, LJS(LT)) == 0)
  {
    status = LT;
  }
  else if (strcmp(content, LJS(GT)) == 0)
  {
    status = GT;
  }
  else if (strcmp(content, LJS(LTEQ)) == 0)
  {
    status = LTEQ;
  }
  else if (strcmp(content, LJS(GTEQ)) == 0)
  {
    status = GTEQ;
  }
  else if (strcmp(content, LJS(EQ2)) == 0)
  {
    status = EQ2;
  }
  else if (strcmp(content, LJS(NOTEQ)) == 0)
  {
    status = NOTEQ;
  }
  else if (strcmp(content, LJS(EQ3)) == 0)
  {
    status = EQ3;
  }
  else if (strcmp(content, LJS(NOTEQ2)) == 0)
  {
    status = NOTEQ2;
  }
  else if (strcmp(content, LJS(MINUS)) == 0)
  {
    status = MINUS;
  }
  else if (strcmp(content, LJS(STAR)) == 0)
  {
    status = STAR;
  }
  else if (strcmp(content, LJS(PERCENT)) == 0)
  {
    status = PERCENT;
  }
  else if (strcmp(content, LJS(STAR2)) == 0)
  {
    status = STAR2;
  }
  else if (strcmp(content, LJS(PLUS2)) == 0)
  {
    status = PLUS2;
  }
  else if (strcmp(content, LJS(MINUS2)) == 0)
  {
    status = MINUS2;
  }
  else if (strcmp(content, LJS(LSHIFT)) == 0)
  {
    status = LSHIFT;
  }
  else if (strcmp(content, LJS(RSHIFT)) == 0)
  {
    status = RSHIFT;
  }
  else if (strcmp(content, LJS(GT3)) == 0)
  {
    status = GT3;
  }
  else if (strcmp(content, LJS(AMPER)) == 0)
  {
    status = AMPER;
  }
  else if (strcmp(content, LJS(PIPE)) == 0)
  {
    status = CAROT;
  }
  else if (strcmp(content, LJS(EXCLAMATION)) == 0)
  {
    status = EXCLAMATION;
  }
  else if (strcmp(content, LJS(TILDE)) == 0)
  {
    status = TILDE;
  }
  else if (strcmp(content, LJS(AMPER2)) == 0)
  {
    status = AMPER2;
  }
  else if (strcmp(content, LJS(PIPE2)) == 0)
  {
    status = PIPE2;
  }
  else if (strcmp(content, LJS(QUESTION2)) == 0)
  {
    status = QUESTION2;
  }
  else if (strcmp(content, LJS(QUESTION)) == 0)
  {
    status = QUESTION;
  }
  else if (strcmp(content, LJS(COLON)) == 0)
  {
    status = COLON;
  }
  else if (strcmp(content, LJS(EQ)) == 0)
  {
    status = EQ;
  }
  else if (strcmp(content, LJS(PLUSEQ)) == 0)
  {
    status = PLUSEQ;
  }
  else if (strcmp(content, LJS(MINUSEQ)) == 0)
  {
    status = MINUSEQ;
  }
  else if (strcmp(content, LJS(TIMESEQ)) == 0)
  {
    status = TIMESEQ;
  }
  else if (strcmp(content, LJS(PERCENTEQ)) == 0)
  {
    status = PERCENTEQ;
  }
  else if (strcmp(content, LJS(TIME2SEQ)) == 0)
  {
    status = TIME2SEQ;
  }
  else if (strcmp(content, LJS(LSHIFTEQ)) == 0)
  {
    status = LSHIFTEQ;
  }
  else if (strcmp(content, LJS(RSHIFTEQ)) == 0)
  {
    status = RSHIFTEQ;
  }
  else if (strcmp(content, LJS(GT3EQ)) == 0)
  {
    status = GT3EQ;
  }
  else if (strcmp(content, LJS(AMPEREQ)) == 0)
  {
    status = AMPEREQ;
  }
  else if (strcmp(content, LJS(PIPEEQ)) == 0)
  {
    status = PIPEEQ;
  }
  else if (strcmp(content, LJS(CAROTEQ)) == 0)
  {
    status = CAROTEQ;
  }
  else if (strcmp(content, LJS(ARROW)) == 0)
  {
    status = ARROW;
  }
  else if (strcmp(content, LJS(DIV)) == 0)
  {
    status = DIV;
  }
  else if (strcmp(content, LJS(DIVEQ)) == 0)
  {
    status = DIVEQ;
  }
  else if (strcmp(content, LJS(RBRACE)) == 0)
  {
    status = RBRACE;
  }
  else
  {
    nt_error(pos);
  }
  return finish(pos);
}

__LJS_NT_Return *next_token(int position)
{
  nt_init();
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
        status = IDENT;
        continue;
      }
      else if (is_punctuator_single(c))
      {
        return punctuator_finish(pos);
      }
      else if (is_punctuator_part(c))
      {
        status = PUNCTUATOR;
        continue;
      }
      else
      {
        nt_error(pos);
      }
      break;
    case IDENT:
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
    case PUNCTUATOR:
      c = get_char(pos++);
      if (is_punctuator_part(c))
      {
        content[content_loc++] = c;
        continue;
      }
      else
      {
        return punctuator_finish(--pos);
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