import subprocess

QJS = 'qjs_debug ./source.txt'
LITEJS = 'gcc template.c -lm && ./a.out'

CMD1 = LITEJS
CMD2 = QJS
RET1 = subprocess.run(CMD1,
                      shell=True,
                      stdout=subprocess.PIPE,
                      stderr=subprocess.PIPE,
                      encoding="utf-8")
RET2 = subprocess.run(CMD2,
                      shell=True,
                      stdout=subprocess.PIPE,
                      stderr=subprocess.PIPE,
                      encoding="utf-8")
RES1 = RET1.stdout.split("\n")
RES2 = RET2.stdout.split("\n")
while len(RES1) < len(RES2):
    RES1.append("")
while len(RES1) > len(RES2):
    RES2.append("")

print("%s|%s" % ("=====LITEJS=====".ljust(30), "=====QUICKJS=====".ljust(30)))
for i in range(len(RES1)):
    print("%s|%s" % (RES1[i].ljust(30), RES2[i].ljust(30)))
