#!/usr/bin/env python

import codecs
import sys

from HTMLParser import HTMLParser

class TemplateParser(HTMLParser):
    output = None
    text = None
    
    def __init__(self, output):
        HTMLParser.__init__(self)
        self.output = output
        self.text = u''
        
        
    def flush_text(self):
        if self.text == u'':
            return
        
        o = self.output
        o.write('    output << "')
        o.write(encode_cpp_string(self.text))
        o.write('";\n')
        self.text = u''
        
        
    def handle_starttag(self, tag, attrs):
        self.text += self.get_starttag_text()
        
    def handle_endtag(self, tag):
        self.text += u'</%s>' % tag
        
        
    def handle_startendtag(self, tag, attrs):
        self.text += self.get_starttag_text()
        
        
    def handle_data(self, data):
        self.text += data
        
        
    def handle_entityref(self, name):
        self.text += u'&%s;' % name
        
        
    def handle_charref(self, name):
        self.text += u'&#%s;' % name
        
        
    def handle_comment(self, data):
        self.text += u'<!--%s-->' % data
        
        
    def handle_decl(self, decl):
        self.text += u'<!%s>' % decl
    
    
    def handle_pi(self, data):
        if data.endswith(u'?'):
            data = data[:-1]
            
        if data.startswith(u'='):
            first_word,code = u'=',data[1:]
        elif data.startswith(u':'):
            first_word,code = u':',data[1:]
        else:
            first_word,code = [x.strip() for x in data.split(' ', 1)]

        self.handle_generic_pi(first_word, code)
    
    
    def unknown_decl(data):
        self.handle_pi(data)
        
        
    def handle_generic_pi(self, kind, code):
        if kind in ('=', 'echo'):
            self.flush_text()
            o = self.output
            # TODO: #line directive
            o.write('    output << (')
            o.write(decode_special_trigraphs(code))
            o.write(');\n')
            
        elif kind in (':', 'code'):
            self.flush_text()
            o = self.output
            o.write(u'    ')
            o.write(decode_special_trigraphs(code))
            o.write(u'\n')

        else:
            print 'Error: unknown processing instruction type %s' % repr(kind)
            sys.exit(1)



def main(args):
    if len(args) != 4:
        print 'Usage: tc.py NAME INPUT OUTPUT'
        return
    
    name = unicode(args[1])
    in_file = uopen(args[2], 'rt')
    out_file = uopen(args[3], 'wt')
    
    tp = TemplateParser(out_file)
    
    in_header = True
    
    out_file.write(u'#line %d "%s"\n' % (1, args[2]))
    
    def write_template_prologue():
        out_file.write(u'#include <iostream>\n')
        out_file.write(u'template<typename Data>\n')
        out_file.write(u'void expand_%s(std::ostream &output, Data &data)\n' % name)
        out_file.write(u'{\n')
        
    def write_template_epilogue():
        out_file.write(u'}\n')
    
    for line in in_file:
        if in_header:
            if line.strip() == "---":
                in_header = False
                write_template_prologue()
                continue
            
            else:
                out_file.write(line)

        else:
            tp.feed(line)
            
    if in_header:
        write_template_prologue()
        
    tp.flush_text()
        
    write_template_epilogue()


def uopen(path, mode):
    return codecs.open(path, mode, encoding='utf-8')
    
    
def encode_cpp_string(str):
    return (str
        .replace('\\', '\\\\')
        .replace('"', '\\"')
        .replace('\r','\\r')
        .replace('\n','\\n'))
        
        
def decode_special_trigraphs(str):
    return (str
        .replace('??[', '<')
        .replace('??]', '>'))


if __name__ == '__main__':
    import sys
    main(sys.argv)

