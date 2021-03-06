
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include "JsonReader.hpp"

using namespace gdx_cpp::utils;

Object& JsonReader::parse (const std::string& json) {
    char[] data = json.toCharArray();
    return parse(data, 0, data.length);
}

Object& JsonReader::parse (const Reader& reader) throws IOException {
    char[] data = new char[1024];
    int offset = 0;
    while (true) {
        int length = reader.read(data, offset, data.length - offset);
        if (length == -1) break;
        if (length == 0) {
            char[] newData = new char[data.length * 2];
            System.arraycopy(data, 0, newData, 0, data.length);
            data = newData;
        } else
            offset += length;
    }
    return parse(data, 0, offset);
}

Object& JsonReader::parse (const InputStream& input) throws IOException {
    return parse(new InputStreamReader(input, "ISO-8859-1"));
}

Object& JsonReader::parse (const gdx_cpp::files::FileHandle& file) throws IOException {
    return parse(file.read());
}

Object& JsonReader::parse (int offset,int length) {
    int cs, p = 0, pe = data.length, eof = pe, top = 0;
    int[] stack = new int[4];

    int s = 0;
    Array<String> names = new Array(8);
    boolean needsUnescape = false;
    RuntimeException parseRuntimeEx = null;

    boolean debug = false;
    if (debug) System.out.println();

    try {

        // line 3 "../src/com/pennypop/animation/JsonParser.java"
        {
            cs = json_start;
            top = 0;
        }

        // line 8 "../src/com/pennypop/animation/JsonParser.java"
        {
            int _klen;
            int _trans = 0;
            int _acts;
            int _nacts;
            int _keys;
            int _goto_targ = 0;

_goto:
            while (true) {
                switch (_goto_targ) {
                case 0:
                    if (p == pe) {
                        _goto_targ = 4;
                        continue _goto;
                    }
                    if (cs == 0) {
                        _goto_targ = 5;
                        continue _goto;
                    }
                case 1:
_match:
                    do {
                        _keys = _json_key_offsets[cs];
                        _trans = _json_index_offsets[cs];
                        _klen = _json_single_lengths[cs];
                        if (_klen > 0) {
                            int _lower = _keys;
                            int _mid;
                            int _upper = _keys + _klen - 1;
                            while (true) {
                                if (_upper < _lower) break;

                                _mid = _lower + ((_upper - _lower) >> 1);
                                if (data[p] < _json_trans_keys[_mid])
                                    _upper = _mid - 1;
                                else if (data[p] > _json_trans_keys[_mid])
                                    _lower = _mid + 1;
                                else {
                                    _trans += (_mid - _keys);
                                    break _match;
                                }
                            }
                            _keys += _klen;
                            _trans += _klen;
                        }

                        _klen = _json_range_lengths[cs];
                        if (_klen > 0) {
                            int _lower = _keys;
                            int _mid;
                            int _upper = _keys + (_klen << 1) - 2;
                            while (true) {
                                if (_upper < _lower) break;

                                _mid = _lower + (((_upper - _lower) >> 1) & ~1);
                                if (data[p] < _json_trans_keys[_mid])
                                    _upper = _mid - 2;
                                else if (data[p] > _json_trans_keys[_mid + 1])
                                    _lower = _mid + 2;
                                else {
                                    _trans += ((_mid - _keys) >> 1);
                                    break _match;
                                }
                            }
                            _trans += _klen;
                        }
                    } while (false);

                    _trans = _json_indicies[_trans];
                    cs = _json_trans_targs[_trans];

                    if (_json_trans_actions[_trans] != 0) {
                        _acts = _json_trans_actions[_trans];
                        _nacts = (int)_json_actions[_acts++];
                        while (_nacts-- > 0) {
                            switch (_json_actions[_acts++]) {
                            case 0:
                                // line 37 "JsonParser.rl"
                            {
                                s = p;
                                needsUnescape = false;
                            }
                            break;
                            case 1:
                                // line 41 "JsonParser.rl"
                            {
                                needsUnescape = true;
                            }
                            break;
                            case 2:
                                // line 44 "JsonParser.rl"
                            {
                                String name = new String(data, s, p - s);
                                s = p;
                                if (needsUnescape) name = unescape(name);
                                if (debug) System.out.println("name: " + name);
                                names.add(name);
                            }
                            break;
                            case 3:
                                // line 51 "JsonParser.rl"
                            {
                                String value = new String(data, s, p - s);
                                s = p;
                                if (needsUnescape) value = unescape(value);
                                String name = names.size > 0 ? names.pop() : null;
                                if (debug) System.out.println("string: " + name + "=" + value);
                                string(name, value);
                            }
                            break;
                            case 4:
                                // line 59 "JsonParser.rl"
                            {
                                String value = new String(data, s, p - s);
                                s = p;
                                String name = names.size > 0 ? names.pop() : null;
                                if (debug) System.out.println("number: " + name + "=" + Float.parseFloat(value));
                                number(name, value);
                            }
                            break;
                            case 5:
                                // line 66 "JsonParser.rl"
                            {
                                String name = names.size > 0 ? names.pop() : null;
                                if (debug) System.out.println("null: " + name);
                                string(name, null);
                            }
                            break;
                            case 6:
                                // line 71 "JsonParser.rl"
                            {
                                String name = names.size > 0 ? names.pop() : null;
                                if (debug) System.out.println("startObject: " + name);
                                startObject(name);
                                {
                                    if (top == stack.length) {
                                        int[] newStack = new int[stack.length * 2];
                                        System.arraycopy(stack, 0, newStack, 0, stack.length);
                                        stack = newStack;
                                    }
                                    {
                                        stack[top++] = cs;
                                        cs = 12;
                                        _goto_targ = 2;
                                        if (true) continue _goto;
                                    }
                                }
                            }
                            break;
                            case 7:
                                // line 77 "JsonParser.rl"
                            {
                                if (debug) System.out.println("endObject");
                                pop();
                                {
                                    cs = stack[--top];
                                    _goto_targ = 2;
                                    if (true) continue _goto;
                                }
                            }
                            break;
                            case 8:
                                // line 82 "JsonParser.rl"
                            {
                                String name = names.size > 0 ? names.pop() : null;
                                if (debug) System.out.println("startArray: " + name);
                                startArray(name);
                                {
                                    if (top == stack.length) {
                                        int[] newStack = new int[stack.length * 2];
                                        System.arraycopy(stack, 0, newStack, 0, stack.length);
                                        stack = newStack;
                                    }
                                    {
                                        stack[top++] = cs;
                                        cs = 35;
                                        _goto_targ = 2;
                                        if (true) continue _goto;
                                    }
                                }
                            }
                            break;
                            case 9:
                                // line 88 "JsonParser.rl"
                            {
                                if (debug) System.out.println("endArray");
                                pop();
                                {
                                    cs = stack[--top];
                                    _goto_targ = 2;
                                    if (true) continue _goto;
                                }
                            }
                            break;
                            // line 186 "../src/com/pennypop/animation/JsonParser.java"
                            }
                        }
                    }

                case 2:
                    if (cs == 0) {
                        _goto_targ = 5;
                        continue _goto;
                    }
                    if (++p != pe) {
                        _goto_targ = 1;
                        continue _goto;
                    }
                case 4:
                    if (p == eof) {
                        int __acts = _json_eof_actions[cs];
                        int __nacts = (int)_json_actions[__acts++];
                        while (__nacts-- > 0) {
                            switch (_json_actions[__acts++]) {
                            case 4:
                                // line 59 "JsonParser.rl"
                            {
                                String value = new String(data, s, p - s);
                                s = p;
                                String name = names.size > 0 ? names.pop() : null;
                                if (debug) System.out.println("number: " + name + "=" + Float.parseFloat(value));
                                number(name, value);
                            }
                            break;
                            case 5:
                                // line 66 "JsonParser.rl"
                            {
                                String name = names.size > 0 ? names.pop() : null;
                                if (debug) System.out.println("null: " + name);
                                string(name, null);
                            }
                            break;
                            // line 225 "../src/com/pennypop/animation/JsonParser.java"
                            }
                        }
                    }

                case 5:
                }
                break;
            }
        }

        // line 114 "JsonParser.rl"

    } catch (RuntimeException ex) {
        parseRuntimeEx = ex;
    }

    if (p < pe) {
        int lineNumber = 1;
        for (int i = 0; i < p; i++)
            if (data[i] == '\n') lineNumber++;
        throw new IllegalArgumentException("Error parsing JSON on line " + lineNumber + " near: " + new String(data, p, pe - p),
                                           parseRuntimeEx);
    } else if (elements.size != 0) {
        Object element = elements.peek();
        elements.clear();
        if (element instanceof ObjectMap)
            throw new IllegalArgumentException("Error parsing JSON, unmatched brace.");
        else
            throw new IllegalArgumentException("Error parsing JSON, unmatched bracket.");
    }
    Object root = this.root;
    this.root = null;
    return root;
}

char* JsonReader::init__json_actions_0 () {
    return new byte[] {0, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 2, 0, 2, 2, 0, 3, 2, 4, 7, 2, 4, 9, 2, 5,
                       7, 2, 5, 9
                      };
}

short* JsonReader::init__json_key_offsets_0 () {
    return new short[] {0, 0, 11, 13, 15, 24, 27, 29, 33, 35, 36, 37, 38, 44, 46, 48, 52, 63, 65, 67, 72, 76, 85, 88, 96, 98,
                        107, 111, 113, 120, 130, 131, 132, 133, 138, 147, 160, 162, 164, 169, 180, 183, 191, 193, 202, 206, 208, 215, 225, 226,
                        227, 228, 233, 242, 245, 251, 258, 263, 271, 274, 274
                       };
}

char* JsonReader::init__json_trans_keys_0 () {
    return new char[] {32, 34, 45, 48, 91, 110, 123, 9, 13, 49, 57, 34, 92, 34, 92, 34, 47, 92, 98, 102, 110, 114, 116, 117,
                       48, 49, 57, 48, 57, 43, 45, 48, 57, 48, 57, 117, 108, 108, 32, 34, 44, 125, 9, 13, 34, 92, 34, 92, 32, 58, 9, 13, 32,
                       34, 45, 48, 91, 110, 123, 9, 13, 49, 57, 34, 92, 34, 92, 32, 44, 125, 9, 13, 32, 34, 9, 13, 34, 47, 92, 98, 102, 110,
                       114, 116, 117, 48, 49, 57, 32, 44, 46, 69, 101, 125, 9, 13, 48, 57, 32, 44, 69, 101, 125, 9, 13, 48, 57, 43, 45, 48, 57,
                       48, 57, 32, 44, 125, 9, 13, 48, 57, 32, 44, 46, 69, 101, 125, 9, 13, 48, 57, 117, 108, 108, 32, 44, 125, 9, 13, 34, 47,
                       92, 98, 102, 110, 114, 116, 117, 32, 34, 44, 45, 48, 91, 93, 110, 123, 9, 13, 49, 57, 34, 92, 34, 92, 32, 44, 93, 9, 13,
                       32, 34, 45, 48, 91, 110, 123, 9, 13, 49, 57, 48, 49, 57, 32, 44, 46, 69, 93, 101, 9, 13, 48, 57, 32, 44, 69, 93, 101, 9,
                       13, 48, 57, 43, 45, 48, 57, 48, 57, 32, 44, 93, 9, 13, 48, 57, 32, 44, 46, 69, 93, 101, 9, 13, 48, 57, 117, 108, 108,
                       32, 44, 93, 9, 13, 34, 47, 92, 98, 102, 110, 114, 116, 117, 32, 9, 13, 32, 46, 69, 101, 9, 13, 32, 69, 101, 9, 13, 48,
                       57, 32, 9, 13, 48, 57, 32, 46, 69, 101, 9, 13, 48, 57, 32, 9, 13, 0
                      };
}

char* JsonReader::init__json_single_lengths_0 () {
    return new byte[] {0, 7, 2, 2, 7, 1, 0, 2, 0, 1, 1, 1, 4, 2, 2, 2, 7, 2, 2, 3, 2, 7, 1, 6, 0, 5, 2, 0, 3, 6, 1, 1, 1, 3, 7,
                       9, 2, 2, 3, 7, 1, 6, 0, 5, 2, 0, 3, 6, 1, 1, 1, 3, 7, 1, 4, 3, 1, 4, 1, 0, 0
                      };
}

char* JsonReader::init__json_range_lengths_0 () {
    return new byte[] {0, 2, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 2, 0, 0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 0, 0, 0, 1, 1,
                       2, 0, 0, 1, 2, 1, 1, 1, 2, 1, 1, 2, 2, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 1, 0, 0
                      };
}

short* JsonReader::init__json_index_offsets_0 () {
    return new short[] {0, 0, 10, 13, 16, 25, 28, 30, 34, 36, 38, 40, 42, 48, 51, 54, 58, 68, 71, 74, 79, 83, 92, 95, 103, 105,
                        113, 117, 119, 125, 134, 136, 138, 140, 145, 154, 166, 169, 172, 177, 187, 190, 198, 200, 208, 212, 214, 220, 229, 231,
                        233, 235, 240, 249, 252, 258, 264, 268, 275, 278, 279
                       };
}

char* JsonReader::init__json_indicies_0 () {
    return new byte[] {0, 2, 3, 4, 6, 7, 8, 0, 5, 1, 10, 11, 9, 13, 14, 12, 15, 15, 15, 15, 15, 15, 15, 15, 1, 16, 17, 1, 18,
                       1, 19, 19, 20, 1, 20, 1, 21, 1, 22, 1, 23, 1, 24, 25, 26, 27, 24, 1, 29, 30, 28, 32, 33, 31, 34, 35, 34, 1, 35, 36, 37,
                       38, 40, 41, 42, 35, 39, 1, 44, 45, 43, 47, 48, 46, 49, 26, 27, 49, 1, 26, 25, 26, 1, 50, 50, 50, 50, 50, 50, 50, 50, 1,
                       51, 52, 1, 53, 54, 55, 56, 56, 57, 53, 1, 58, 1, 53, 54, 56, 56, 57, 53, 58, 1, 59, 59, 60, 1, 60, 1, 53, 54, 57, 53,
                       60, 1, 53, 54, 55, 56, 56, 57, 53, 52, 1, 61, 1, 62, 1, 63, 1, 64, 65, 66, 64, 1, 67, 67, 67, 67, 67, 67, 67, 67, 1, 68,
                       69, 70, 71, 72, 74, 75, 76, 77, 68, 73, 1, 79, 80, 78, 82, 83, 81, 84, 70, 75, 84, 1, 70, 69, 71, 72, 74, 76, 77, 70,
                       73, 1, 85, 86, 1, 87, 88, 89, 90, 91, 90, 87, 1, 92, 1, 87, 88, 90, 91, 90, 87, 92, 1, 93, 93, 94, 1, 94, 1, 87, 88, 91,
                       87, 94, 1, 87, 88, 89, 90, 91, 90, 87, 86, 1, 95, 1, 96, 1, 97, 1, 98, 99, 100, 98, 1, 101, 101, 101, 101, 101, 101,
                       101, 101, 1, 102, 102, 1, 103, 104, 105, 105, 103, 1, 103, 105, 105, 103, 18, 1, 103, 103, 20, 1, 103, 104, 105, 105,
                       103, 17, 1, 106, 106, 1, 1, 1, 0
                      };
}

char* JsonReader::init__json_trans_targs_0 () {
    return new byte[] {1, 0, 2, 5, 54, 57, 53, 9, 53, 3, 53, 4, 3, 53, 4, 3, 54, 57, 55, 8, 56, 10, 11, 58, 12, 13, 20, 59, 14,
                       15, 34, 14, 15, 34, 15, 16, 17, 22, 23, 29, 19, 30, 19, 18, 19, 21, 18, 19, 21, 19, 18, 23, 29, 19, 20, 24, 26, 59, 25,
                       27, 28, 31, 32, 33, 19, 20, 59, 14, 35, 36, 39, 40, 41, 47, 38, 60, 48, 38, 37, 38, 52, 37, 38, 52, 38, 41, 47, 38, 39,
                       42, 44, 60, 43, 45, 46, 49, 50, 51, 38, 39, 60, 37, 53, 53, 6, 7, 53
                      };
}

char* JsonReader::init__json_trans_actions_0 () {
    return new byte[] {0, 0, 0, 1, 1, 1, 17, 0, 13, 1, 24, 1, 0, 7, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 1, 21, 1, 0, 5,
                       0, 0, 0, 0, 1, 1, 1, 17, 0, 13, 1, 24, 1, 0, 7, 0, 0, 3, 0, 0, 9, 9, 0, 0, 27, 0, 0, 0, 0, 0, 0, 11, 11, 33, 3, 0, 0, 0,
                       1, 1, 1, 17, 19, 0, 13, 1, 24, 1, 0, 7, 0, 0, 0, 0, 9, 9, 0, 0, 30, 0, 0, 0, 0, 0, 0, 11, 11, 36, 3, 0, 9, 0, 0, 11
                      };
}

char* JsonReader::init__json_eof_actions_0 () {
    return new byte[] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 11, 0, 0
                      };
}

void JsonReader::set (const std::string& name,const Object& value) {
    if (current instanceof ObjectMap)
        ((ObjectMap)current).put(name, value);
    else if (current instanceof Array)
        ((Array)current).add(value);
    else
        root = value;
}

void JsonReader::startObject (const std::string& name) {
    ObjectMap value = new ObjectMap();
    if (current != null) set(name, value);
    elements.add(value);
    current = value;
}

void JsonReader::startArray (const std::string& name) {
    Array value = new Array();
    if (current != null) set(name, value);
    elements.add(value);
    current = value;
}

void JsonReader::pop () {
    root = elements.pop();
    current = elements.size > 0 ? elements.peek() : null;
}

void JsonReader::string (const std::string& name,const std::string& value) {
    set(name, value);
}

void JsonReader::number (const std::string& name,const std::string& value) {
    set(name, value);
}

std::string& JsonReader::unescape (const std::string& value) {
    int length = value.length();
    StringBuilder buffer = new StringBuilder(length + 16);
    for (int i = 0; i < length;) {
        char c = value.charAt(i++);
        if (c != '\\') {
            buffer.append(c);
            continue;
        }
        if (i == length) break;
        c = value.charAt(i++);
        if (c == 'u') {
            buffer.append(Character.toChars(Integer.parseInt(value.substring(i, i + 4), 16)));
            i += 4;
            continue;
        }
        switch (c) {
        case '"':
        case '\\':
        case '/':
            break;
        case 'b':
            c = '\b';
            break;
        case 'f':
            c = '\f';
            break;
        case 'n':
            c = '\n';
            break;
        case 'r':
            c = '\r';
            break;
        case 't':
            c = '\t';
            break;
        default:
            throw new SerializationException("Illegal escaped character: \\" + c);
        }
        buffer.append(c);
    }
    return buffer.toString();
}

