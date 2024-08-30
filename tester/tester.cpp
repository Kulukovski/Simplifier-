#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iostream>
#include <set>
#include <queue>
#include <cmath>

class spellchecker
{
private:
    std::vector<std::string> keyboard = {
        "1234567890",
        "qwertyuiop",
        "asdfghjkl",
        "zxcvbnm" };
    struct suggest
    {
        std::string word;
        double diss;
    };
    struct weight
    {
        int diss;
        double dijdiss;
    };
    struct key
    {
        char value;
        int x;
        int y;
    };
    std::unordered_map<char, key> keys;
    std::string spell;
    std::set<std::string> twos;
    std::set<std::string> special;
    std::vector<std::set<std::string>> wordvec;

public:
    spellchecker()
    {
        for (int i = 0; i < keyboard.size(); i++)
        {
            for (int j = 0; j < keyboard[i].size(); j++)
            {
                char val = keyboard[i][j];
                keys[val] = { val, j, i };
            }
        }
        std::string tet;
        std::ifstream two;
        for (int i = 2; i <= 15; i++)
        {
            tet = "words/" + std::to_string(i);
            two.open(tet + ".txt");
            while (two >> spell)
            {
                twos.insert(spell);
            }
            wordvec.push_back(twos);
            twos.clear();
            two.close();
            two.clear();
        }
        std::ifstream specials("words.txt");
        while (specials >> spell)
        {
            special.insert(spell);
        }
    }
    double distn(const key& a, const key& b)
    {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }
    double dijk(char start, char end)
    {
        std::unordered_map<char, double> dist;
        for (const auto& key : keys)
        {
            char val = key.first;
            dist[val] = std::numeric_limits<double>::max();
        }
        dist[start] = 0;
        auto cmp = [&dist](char a, char b)
        { return dist[a] > dist[b]; };
        std::priority_queue<char, std::vector<char>, decltype(cmp)> pq(cmp);
        pq.push(start);
        while (!pq.empty())
        {
            char w = pq.top();
            pq.pop();
            for (const auto& key : keys)
            {
                char v = key.first;
                double othe = dist[w] + distn(keys.at(w), key.second);
                if (othe < dist[v])
                {
                    dist[v] = othe;
                    pq.push(v);
                }
            }
        }
        return dist[end];
    }
    weight lev(std::string s1, std::string s2)
    {
        double diss = 0;
        const size_t w1 = s1.size();
        const size_t w2 = s2.size();
        std::vector<std::vector<int>> d(w1 + 1, std::vector<int>(w2 + 1));

        for (size_t i = 0; i <= w1; i++)
        {
            d[i][0] = i;
        }
        for (size_t j = 0; j <= w2; j++)
        {
            d[0][j] = j;
        }

        for (size_t j = 1; j <= w2; j++)
        {
            for (size_t i = 1; i <= w1; i++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    d[i][j] = d[i - 1][j - 1];
                }
                else
                {
                    int minv = d[i - 1][j] + 1;
                    if (d[i][j - 1] + 1 < minv)
                    {
                        minv = d[i][j - 1] + 1;
                    }
                    if (d[i - 1][j - 1] + 1 < minv)
                    {
                        minv = d[i - 1][j - 1] + 1;
                    }
                    d[i][j] = minv;
                }
            }
        }

        if (d[w1][w2] == 1 && w1 == w2)
        {
            int i1 = 0;
            int fla = 0;
            do
            {
                if (s1[i1] != s2[i1])
                {
                    diss = dijk(s1[i1], s2[i1]);
                    fla = 1;
                }
                i1++;
            } while (fla == 0);
        }
        if ((d[w1][w2] == 1) && w1 > w2)
        {
            diss = 1.1;
        }
        if ((d[w1][w2] == 1) && w1 < w2)
        {
            diss = 1.1;
        }
        if ((d[w1][w2] == 2) && w1 == w2)
        {
            char a[100];
            int c = 0;
            for (int i = 0; i <= w1; i++)
            {
                if (s1[i] != s2[i])
                {
                    a[c] = i;
                    c++;
                }
            }
            char f = s1[a[0]];
            s1[a[0]] = s1[a[1]];
            s1[a[1]] = f;
            if (s1 == s2)
            {
                d[w1][w2] = 1;
                diss = 0.5;
            }
        }

        weight result = { d[w1][w2], diss };
        return result;
    }

    std::string check(std::string a)
    {
        int len = a.length() - 3;
        std::set<std::string>::iterator it;
        suggest bestword{ "", 2 };
        suggest otherword{ "", 2 };

        for (int i = 0; i <= 2; i++)
        {

            if (len <= -2)
            {
                return "";
            }
            if (len == -1)
            {
                i++;
            }
            if (len + i >= 14)
            {
                return "";
            }
            it = wordvec[len + i].begin();
            while (it != wordvec[len + i].end())
            {
                if (lev(a, *it).diss == 1 || lev(a, *it).diss == 0)
                {
                    std::cout << a << ' ' << *it << ' ' << lev(a, *it).dijdiss << "\n\n";
                    if (lev(a, *it).dijdiss <= bestword.diss)
                    {
                        otherword = bestword;
                        bestword.word = *it;
                        bestword.diss = lev(a, *it).dijdiss;
                    }
                }
                it++;
            }
        }
        return bestword.word;
    }

    int spelling(std::string a)
    {
        int len = a.length() - 2;

        for (int i = 0; i < a.length(); i++)
        {
            if (isdigit(a[i]))
            {
                return 1;
            }
            if (a[i] == '-')
            {
                return 1;
            }
        }
        if (a.length() > 3 && a[a.length() - 2] == '\'')
        {
            a.resize(a.size() - 2);
            len -= 2;
        }
        if (a.length() <= 1 || a.length() >= 16)
        {
            return 1;
        }
        if (isupper(a[0]))
        {
            return 1;
        }
        if (special.find(a) != special.end())
        {
            return 1;
        }
        if (wordvec[len].find(a) == wordvec[len].end())
        {
            return 0;
        }
        else
        {

            return 1;
        }
    }
    void tester()
    {
        std::set<std::string>::iterator it = twos.begin();

        while (it != twos.end())
        {
            std::cout << *it << "\n";
            it++;
        }
    }
};

std::string replace(std::string& s)
{
    for (std::string::size_type i = 0; i < s.size(); i++)
    {
        if (s[i] == '_')
        {
            s[i] = ' ';
        }
    }
    return s;
}

std::string tolow(const std::string& s)
{
    std::string result;
    result.reserve(s.size());

    for (char c : s)
    {
        result += std::tolower(c);
    }

    return result;
}

std::vector<std::string> tsen(const std::string& text)
{
    std::vector<std::string> sent;
    std::string sen;

    for (char c : text)
    {
        sen += c;
        if (c == '.' || c == '!' || c == '?')
        {
            sent.push_back(sen);
            sen.clear();
        }
    }

    if (!sen.empty())
    {
        sent.push_back(sen);
    }

    return sent;
}

std::vector<std::string> twords(const std::string& sen)
{
    std::vector<std::string> words;
    std::istringstream sss(sen);
    std::string word;
    std::string last;

    while (sss >> word)
    {
        if (word.front() == ',' || word.front() == ')' || word.front() == '(' || word.front() == ';' || word.front() == ':')
        {
            last = word.front();
            word.erase(0, 1);
            words.push_back(last);
            words.push_back(word);
        }

        if (word.back() == '.' || word.back() == '!' || word.back() == '?' || word.back() == ',' 
            || word.back() == ')' || word.back() == '(' || word.back() == ';' || word.back() == ':')
        {
            last = word.back();
            word.resize(word.size() - 1);
            words.push_back(word);
            words.push_back(last);
        }
        else
        {
            words.push_back(word);
        }
    }

    return words;
}

int main()
{
    std::unordered_map<std::string, std::string> dictionary;
    spellchecker spells;
    std::vector<std::string> additions;
    std::string check;
    std::ifstream file("dictionary.txt");
    std::string comp, simp;

    while (file >> comp >> simp)
    {
        dictionary[comp] = simp;
    }

    std::ifstream fi("file.txt");
    std::ofstream out("output.txt");
    std::string text((std::istreambuf_iterator<char>(fi)), std::istreambuf_iterator<char>());
    file.close();
    std::vector<std::string> sentences = tsen(text);

    for (const std::string& sentence : sentences)
    {
        std::vector<std::string> words = twords(sentence);
        int counter = 0;
        for (const std::string& word : words)
        {
            check = word;

            if (spells.spelling(word) == 0)
            {
                check = spells.check(word);

                if (check == "")
                {
                    check = word;
                }
            }

            if (dictionary[tolow(check)].empty() == 0)
            {
                check = replace(dictionary[tolow(check)]);
                if (check.back() == '.')
                {
                    additions.push_back(check);
                    check = word + "*";
                }
            }

            if (counter == (words.size() - 2))
            {
                out << check;
            }
            else
            {
                out << check << ' ';
            }
            counter++;
        }
    }

    out << "\n\n\n";
    for (unsigned int i = 0; i < additions.size(); i++)
    {
        out << additions[i] << "\n";
    }
}