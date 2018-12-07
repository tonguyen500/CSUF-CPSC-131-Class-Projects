//
//  concordance
//

#ifndef concordance_solution_h
#define concordance_solution_h

#include <iostream>
#include <map>            /* std::multimap<T> and std::map<T> (not used) */
#include <list>
#include <vector>
#include <algorithm>      /* std::transform */
#include <string>         /* not needed for Mac OSX */


class StringLenCmp {
public:
	StringLenCmp() = default;

	// sort by length first, and then alphabetically
	bool operator()(const std::string& a, const std::string& b) const {
		return (a.size() < b.size()) || (a.size() == b.size() && a < b);
	}

private:
	// no data
};


class concordance {
	typedef std::multimap<std::string, size_t, StringLenCmp> wordDictType;

public:
	concordance(size_t minwordlen = 1, size_t maxwordlen = 40)
		: minwordlen_(minwordlen), maxwordlen_(maxwordlen), words_at_length_() {
		for (size_t i = 0; i < MAXWORDLEN; ++i) {
			words_at_length_.push_back(0);
		}
	}

	void add_word(const std::string&, size_t); // TO DO
	size_t total_words() const; // TO DO
	size_t total_words(size_t length) const; // TO DO
	void print(std::ostream&) const; // TO DO

	void read_text(std::istream&, const std::string&); // ALREADY DONE

private:
	static const size_t MAXWORDLEN = 50;

	wordDictType word_map_; // multimap with key=word and value=page number
	size_t minwordlen_;
	size_t maxwordlen_;
	std::vector<size_t> words_at_length_; // number of words of each length
};

// ALREADY DONE: BREAK A LINE INTO A LIST OF WORDS
// Courtesy of Martin Broadhurst -- http://www.martinbroadhurst.com/how-to-split-a-string-in-c.html
template <class Container>
void split(const std::string& str, Container& cont, const std::string& delims = " ") {
	std::size_t curr, prev = 0;
	curr = str.find_first_of(delims);

	while (curr != std::string::npos) {                   // largest possible unsigned number
		cont.push_back(str.substr(prev, curr - prev));
		prev = curr + 1;
		curr = str.find_first_of(delims, prev);
	}

	cont.push_back(str.substr(prev, curr - prev));
}

// ALREADY DONE: READ FROM A TEXT FILE LINE BY LINE
void concordance::read_text(std::istream& in, const std::string& ignore) {
	std::string line;

	for (size_t i = 1; getline(in, line, '\n'); i++) {
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);

		typedef std::list<std::string> container;
		container words;                          // split into container, dump ignore chars
		split<container>(line, words, ignore);

		typename container::const_iterator cit;
		for (cit = words.cbegin(); cit != words.cend(); ++cit) { add_word(*cit, i); }
	}
}

// TO DO: add a (word, line_number) to the multimap. Do not add if the same (word, line_number) is already present
void concordance::add_word(const std::string& word, size_t line)
{
    if(word_map_.find(word) == word_map_.end())
    {
        word_map_.insert(std::pair<std::string,size_t>(word,line));
        words_at_length_[word.length()]++;
    }
    else{
        auto word_iter = word_map_.equal_range(word);
        for(auto line_iter = word_iter.first; line_iter!=word_iter.second;line_iter++)
        {
            if(line_iter->second == line){
                return;
            }
        }
        word_map_.insert(std::pair<std::string,size_t>(word,line));
    }
}

// TO DO: return the total number of words of length size
size_t concordance::total_words(size_t size) const
{
    return words_at_length_[size];
}

// TO DO: return the total number of words of all lengths
size_t concordance::total_words() const
{
    size_t  total = 0;
    for (size_t i = minwordlen_; i != maxwordlen_+1; ++i)
    {
        total += words_at_length_[i];
    }
    return total;

}

// TO DO: print list of words and line numbers as shown in example_concordances.txt in Project requirements document
void concordance::print(std::ostream& out) const
{
   wordDictType::const_iterator it;
                                                        //YOu should use upper bound here
    for( auto it = word_map_.cbegin(); it != word_map_.cend(); it = word_map_.upper_bound((it->first)))
    {
        auto it2 = word_map_.equal_range(it->first);
        std::cout<<it->first<<": ";
        for ( auto it3 = it2.first; it3 != it2.second; it3++)
        {
            std::cout <<it3->second<< ' ';

        }
        std::cout <<'\n';
    }
}

#endif /* concordance_solution_h */
