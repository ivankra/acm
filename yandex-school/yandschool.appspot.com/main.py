#!/usr/bin/env python
# coding: utf-8
import re, cgi, wsgiref.handlers
from google.appengine.ext import webapp

class StatusException(Exception):
    def __init__(self, value):
        self.value = value
    
    def __str__(self):
        return self.value

def Normalize(text):
    return re.sub(r'\s+', ' ', text).strip()

def GetProblemNumber(text, numberOfProblems):
    text = Normalize(text)
    if len(text) == 0:
        raise StatusException('Строка пуста')

    result = 0
    for c in text:
        if ord(c) >= 128:
            raise StatusException('Используйте только<br/>буквы латинского алфавита')
        result = result * 239 + ord(c)

    # delicately convert result to a signed 32-bit integer
    result &= 0xFFFFFFFFL
    if result & 0x80000000L:
        result = -(result ^ 0xFFFFFFFFL) - 1

    return (result % numberOfProblems + numberOfProblems) % numberOfProblems + 1;


class MainHandler(webapp.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/html; charset=utf-8'
        argQ = Normalize(self.request.get('q', ''))
        argN = self.request.get('n', '').strip()
        status = self.getStatusString(argQ, argN)
        if argN == '':
            argN = '4'
        self.response.out.write(self.renderPage(argQ, argN, status))
        
    def getStatusString(self, argQ, argN):
        if argQ == '' and argN == '':
            return ''

        try:
            try:
                n = int(argN)
                if n < 1 or n > 100:
                    raise Exception()
            except:
                raise StatusException('Число задач указано неправильно')

            return 'Ваш номер задачи: %d' % GetProblemNumber(argQ, n)

        except StatusException, e:
            return '<span style="font-weight: bold; color: #ff0000">%s</font>' % e

    def renderPage(self, q, n, status):
        try:
            qenc = cgi.escape(q, True).encode('utf-8')
        except:
            qenc = ''

        options = ''.join(
            ['<option value="%d"%s>%d</option>\n' %
             (i, (' selected="selected"' if (str(i) == n) else ''), i) for i in range(2, 10)])

        html = '''<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Узнай номер своей задачи (ШАД - Алгоритмы 1 - 2009)</title>
</head>
<body>
<form action="/alg" method="GET">
<table border="0">
  <tr>
    <td>Кодовое слово:</td>
    <td><input id="q" name="q" type="text" size="30" value="%(qenc)s" />
  </tr>
  <tr>
    <td>Число задач:</td>
    <td>
      <select id="n" name="n">%(options)s</select>
    </td>
  </tr>
  <tr>
    <td colspan="2" align="center">
      <input type="submit" value="Отправить" />
    </td>
  </tr>
  <tr>
    <td colspan="2" align="center">
      <br />
      %(status)s
    </td>
  </tr>
</table>
</form>
<script>document.getElementById("q").focus();</script>
</body>
</html>'''
        return html % locals()


def main():
    application = webapp.WSGIApplication([('/', MainHandler), ('/alg', MainHandler)], debug=True)
    wsgiref.handlers.CGIHandler().run(application)

if __name__ == '__main__':
    main()
