#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <uchar.h>

// char a[] = u8"\u000b";
// char b[] = u8"\u000c";

// status
enum
{
  INITIAL,
  WHITE_SPACE,
};

char source_code[1024];

#define LJS(content) __LJS_##content
#define __LJS_TAB ('\t')
#define __LJS_SP (' ')
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
  status = INITIAL;
}

char get_char(int position)
{
  return source_code[position];
}

__LJS_NT_Return *next_token(int position)
{
  init();
  int pos = position;
  while (1)
  {
    switch (status)
    {
    case INITIAL:
      c = get_char(pos++);
      content[content_loc++] = c;
      if (c == LJS(TAB) || c == LJS(SP))
      {
        status = WHITE_SPACE;
        continue;
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
    printf("%s\n", translate(res->token->type));
  }

  fclose(fp);
  return 0;
}
