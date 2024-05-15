#include "hangman.h"
#include <iostream>
#include <string>
#include <string_view>
#include <random>
#include <limits> // for std::numeric_limits
#include <cctype> // for std::isalpha and tolower
#include <algorithm> // for std::find
#include <vector> // for std::vector

// Array of strings for the stages of hangman, purely prints the index based of input int
void printMan(int x) {
	std::string_view man [] {
	"------\n"
	"|    |\n"
	"|    O\n"
	"|   /|\\\n"
	"|    |\n"
	"|   / \\\n"
	"|\n"
	"-------\n",
	"------\n"
	"|    |\n"
	"|    O\n"
	"|   /|\\\n"
	"|    |\n"
	"|   /\n"
	"|\n"
	"-------\n",
	"------\n"
	"|    |\n"
	"|    O\n"
	"|   /|\\\n"
	"|    |\n"
	"|\n"
	"|\n"
	"-------\n",
	"------\n"
	"|    |\n"
	"|    O\n"
	"|   /|\n"
	"|    |\n"
	"|\n"
	"|\n"
	"-------\n",
	"------\n"
	"|    |\n"
	"|    O\n"
	"|    |\n"
	"|    |\n"
	"|\n"
	"|\n"
	"-------\n",
	"------\n"
	"|    |\n"
	"|    O\n"
	"|\n"
	"|\n"
	"|\n"
	"|\n"
	"-------\n",
	"------\n"
	"|    |\n"
	"|\n"
	"|\n"
	"|\n"
	"|\n"
	"|\n"
	"-------\n"};
	std::cout << man[x];
}

// Returns a random string for the player to guess
std::string_view getWord() {
	std::vector<std::string_view> words {"about", "above", "abuse", "accept", "accident", "accuse", "across", "activist", "actor", "administration", "admit", "adult", "advertise", "advise", "affect", "afraid", "after", "again", "against", "agency", "aggression", "agree", "agriculture", "force", "airplane", "airport", "album", "alcohol", "alive", "almost", "alone", "along", "already", "although", "always", "ambassador", "amend", "ammunition", "among", "amount", "anarchy", "ancestor", "ancient", "anger", "animal", "anniversary", "announce", "another", "answer", "apologize", "appeal", "appear", "appoint", "approve", "archeology", "argue", "around", "arrest", "arrive", "artillery", "assist", "astronaut", "astronomy", "asylum", "atmosphere", "attach", "attack", "attempt", "attend", "attention", "automobile", "autumn", "available", "average", "avoid", "awake", "award", "balance", "balloon", "ballot", "barrier", "battle", "beauty", "because", "become", "before", "begin", "behavior", "behind", "believe", "belong", "below", "betray", "better", "between", "biology", "black", "blame", "bleed", "blind", "block", "blood", "border", "borrow", "bottle", "bottom", "boycott", "brain", "brave", "bread", "break", "breathe", "bridge", "brief", "bright", "bring", "broadcast", "brother", "brown", "budget", "build", "building", "bullet", "burst", "business", "cabinet", "camera", "campaign", "cancel", "cancer", "candidate", "capital", "capture", "career", "careful", "carry", "catch", "cause", "ceasefire", "celebrate", "center", "century", "ceremony", "chairman", "champion", "chance", "change", "charge", "chase", "cheat", "cheer", "chemicals", "chemistry", "chief", "child", "children", "choose", "circle", "citizen", "civilian", "civil", "rights", "claim", "clash", "class", "clean", "clear", "clergy", "climate", "climb", "clock", "close", "cloth", "clothes", "cloud", "coalition", "coast", "coffee", "collapse", "collect", "college", "colony", "color", "combine", "command", "comment", "committee", "common", "communicate", "community", "company", "compare", "compete", "complete", "complex", "compromise", "computer", "concern", "condemn", "condition", "conference", "confirm", "conflict", "congratulate", "Congress", "connect", "conservative", "consider", "constitution", "contact", "contain", "container", "continent", "continue", "control", "convention", "cooperate", "correct", "corruption", "cotton", "count", "country", "court", "cover", "crash", "create", "creature", "credit", "crime", "criminal", "crisis", "criticize", "crops", "cross", "crowd", "crush", "culture", "curfew", "current", "custom", "customs", "damage", "dance", "danger", "daughter", "debate", "decide", "declare", "decrease", "defeat", "defend", "deficit", "define", "degree", "delay", "delegate", "demand", "democracy", "demonstrate", "denounce", "depend", "deplore", "deploy", "depression", "describe", "desert", "design", "desire", "destroy", "detail", "detain", "develop", "device", "dictator", "different", "difficult", "dinner", "diplomat", "direct", "direction", "disappear", "disarm", "disaster", "discover", "discrimination", "discuss", "disease", "dismiss", "dispute", "dissident", "distance", "divide", "doctor", "document", "dollar", "donate", "double", "dream", "drink", "drive", "drown", "during", "early", "earth", "earthquake", "ecology", "economy", "education", "effect", "effort", "either", "elect", "electricity", "embassy", "embryo", "emergency", "emotion", "employ", "empty", "enemy", "energy", "enforce", "engine", "engineer", "enjoy", "enough", "enter", "environment", "equal", "equipment", "escape", "especially", "establish", "estimate", "ethnic", "evaporate", "event", "every", "evidence", "exact", "examine", "example", "excellent", "except", "exchange", "excuse", "execute", "exercise", "exile", "exist", "expand", "expect", "expel", "experience", "experiment", "expert", "explain", "explode", "explore", "export", "express", "extend", "extra", "extraordinary", "extreme", "extremist", "factory", "false", "family", "famous", "father", "favorite", "federal", "female", "fence", "fertile", "field", "fierce", "fight", "final", "financial", "finish", "fireworks", "first", "float", "flood", "floor", "flower", "fluid", "follow", "force", "foreign", "forest", "forget", "forgive", "former", "forward", "freedom", "freeze", "fresh", "friend", "frighten", "front", "fruit", "funeral", "future", "gather", "general", "generation", "genocide", "gentle", "glass", "goods", "govern", "government", "grain", "grass", "great", "green", "grind", "ground", "group", "guarantee", "guard", "guerrilla", "guide", "guilty", "happen", "happy", "harvest", "headquarters", "health", "heavy", "helicopter", "hijack", "history", "holiday", "honest", "honor", "horrible", "horse", "hospital", "hostage", "hostile", "hotel", "house", "however", "human", "humor", "hunger", "hurry", "husband", "identify", "ignore", "illegal", "imagine", "immediate", "immigrant", "import", "important", "improve", "incident", "incite", "include", "increase", "independent", "individual", "industry", "infect", "inflation", "influence", "inform", "information", "inject", "injure", "innocent", "insane", "insect", "inspect", "instead", "instrument", "insult", "intelligence", "intelligent", "intense", "interest", "interfere", "international", "Internet", "intervene", "invade", "invent", "invest", "investigate", "invite", "involve", "island", "issue", "jewel", "joint", "judge", "justice", "kidnap", "knife", "knowledge", "labor", "laboratory", "language", "large", "laugh", "launch", "learn", "leave", "legal", "legislature", "letter", "level", "liberal", "light", "lightning", "limit", "liquid", "listen", "literature", "little", "local", "lonely", "loyal", "machine", "magazine", "major", "majority", "manufacture", "march", "market", "marry", "material", "mathematics", "matter", "mayor", "measure", "media", "medicine", "member", "memorial", "memory", "mental", "message", "metal", "method", "microscope", "middle", "militant", "military", "militia", "mineral", "minister", "minor", "minority", "minute", "missile", "missing", "mistake", "model", "moderate", "modern", "money", "month", "moral", "morning", "mother", "motion", "mountain", "mourn", "movement", "movie", "murder", "music", "mystery", "narrow", "nation", "native", "natural", "nature", "necessary", "negotiate", "neighbor", "neither", "neutral", "never", "night", "noise", "nominate", "normal", "north", "nothing", "nowhere", "nuclear", "number", "object", "observe", "occupy", "ocean", "offensive", "offer", "office", "officer", "official", "often", "operate", "opinion", "oppose", "opposite", "oppress", "orbit", "order", "organize", "other", "overthrow", "paint", "paper", "parachute", "parade", "pardon", "parent", "parliament", "partner", "party", "passenger", "passport", "patient", "peace", "people", "percent", "perfect", "perform", "period", "permanent", "permit", "person", "persuade", "physical", "physics", "picture", "piece", "pilot", "place", "planet", "plant", "plastic", "please", "plenty", "point", "poison", "police", "policy", "politics", "pollute", "popular", "population", "position", "possess", "possible", "postpone", "poverty", "power", "praise", "predict", "pregnant", "present", "president", "press", "pressure", "prevent", "price", "prison", "private", "prize", "probably", "problem", "process", "produce", "profession", "professor", "profit", "program", "progress", "project", "promise", "propaganda", "property", "propose", "protect", "protest", "prove", "provide", "public", "publication", "publish", "punish", "purchase", "purpose", "quality", "question", "quick", "quiet", "radar", "radiation", "radio", "railroad", "raise", "reach", "react", "ready", "realistic", "reason", "reasonable", "rebel", "receive", "recent", "recession", "recognize", "record", "recover", "reduce", "reform", "refugee", "refuse", "register", "regret", "reject", "relations", "release", "religion", "remain", "remains", "remember", "remove", "repair", "repeat", "report", "represent", "repress", "request", "require", "rescue", "research", "resign", "resist", "resolution", "resource", "respect", "responsible", "restaurant", "restrain", "restrict", "result", "retire", "return", "revolt", "right", "river", "rocket", "rough", "round", "rubber", "rural", "sabotage", "sacrifice", "sailor", "satellite", "satisfy", "school", "science", "search", "season", "second", "secret", "security", "seeking", "seize", "Senate", "sense", "sentence", "separate", "series", "serious", "serve", "service", "settle", "several", "severe", "shake", "shape", "share", "sharp", "sheep", "shell", "shelter", "shine", "shock", "shoot", "short", "should", "shout", "shrink", "sickness", "signal", "silence", "silver", "similar", "simple", "since", "single", "sister", "situation", "skeleton", "skill", "slave", "sleep", "slide", "small", "smash", "smell", "smoke", "smooth", "social", "soldier", "solid", "solve", "sound", "south", "space", "speak", "special", "speech", "speed", "spend", "spill", "spirit", "split", "sport", "spread", "spring", "square", "stand", "start", "starve", "state", "station", "statue", "steal", "steam", "steel", "stick", "still", "stone", "store", "storm", "story", "stove", "straight", "strange", "street", "stretch", "strike", "strong", "structure", "struggle", "study", "stupid", "subject", "submarine", "substance", "substitute", "subversion", "succeed", "sudden", "suffer", "sugar", "suggest", "suicide", "summer", "supervise", "supply", "support", "suppose", "suppress", "surface", "surplus", "surprise", "surrender", "surround", "survive", "suspect", "suspend", "swallow", "swear", "sweet", "sympathy", "system", "target", "taste", "teach", "technical", "technology", "telephone", "telescope", "television", "temperature", "temporary", "tense", "terrible", "territory", "terror", "terrorist", "thank", "theater", "theory", "there", "these", "thick", "thing", "think", "third", "threaten", "through", "throw", "tired", "today", "together", "tomorrow", "tonight", "torture", "total", "touch", "toward", "trade", "tradition", "traffic", "tragic", "train", "transport", "transportation", "travel", "treason", "treasure", "treat", "treatment", "treaty", "trial", "tribe", "trick", "troops", "trouble", "truce", "truck", "trust", "under", "understand", "unite", "universe", "university", "unless", "until", "urgent", "usual", "vacation", "vaccine", "valley", "value", "vegetable", "vehicle", "version", "victim", "victory", "video", "village", "violate", "violence", "visit", "voice", "volcano", "volunteer", "wages", "waste", "watch", "water", "wealth", "weapon", "weather", "weigh", "welcome", "wheat", "wheel", "where", "whether", "which", "while", "white", "whole", "willing", "window", "winter", "withdraw", "without", "witness", "woman", "wonder", "wonderful", "world", "worry", "worse", "worth", "wound", "wreck", "wreckage", "write", "wrong", "yellow", "yesterday", "young"};
	std::random_device rd; // Use std::random_device to obtain a seed for the random number engine
    std::mt19937 rng(rd()); // Use std::mt19937 as the random number engine (Mersenne Twister)
    std::uniform_int_distribution<long long unsigned> distribution(0, words.size() - 1); // Uniform distribution over options array
    return words[distribution(rng)];
}

// Checks validity of user input, returns false if the input is more than a single letter, or if it's not an alphanumeric character
bool isValid(char entry) {
	std::cout << "\033[2J\033[1;1H"; //ANSI escape sequence to clear the screen
	if (std::cin.fail() || std::cin.peek() != '\n' || !std::isalpha(entry)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Please enter a single valid character\n";
		return false;
	}
	return true;
}

// Asks for user input, then passes it to isValid to ensure valid entry was made. Will not return yhr character until a valid entry is read
char getGuess() {
	char guess {};
	do {
		std::cout << "Enter a letter to guess: ";
		std::cin >> guess;
		guess = char(tolower(guess));
	} while(!isValid(guess));
	return guess;
}

// Checks if user entry is in the word to guess
bool inWord(char ch, std::string_view sv) {
	// Use std::find to search for the character in the string_view
    auto it = std::find(sv.begin(), sv.end(), ch);
    
    // Check if the character was found
    return it != sv.end();
}

bool wasGuessed(char ch, std::vector<char>& vc) {
	// Use std::find to search for the character in the vector
    auto it = std::find(vc.begin(), vc.end(), ch);
    
    // Check if the character was found
    return it != vc.end();
}

// Iterates through the guess string and replaces the appropriate blanks with the guessed letter
void replace(char ch, std::string_view sv, std::string& wd) {
	for (long long unsigned i = 0; i <=sv.length(); ++i) {
		if (sv[i] == ch) {
			wd[i * 2] = ch;
		}
	}
}

void hangmanMain () {
	std::string_view word {getWord()};
	std::string guessString {};
	std::vector<char> previousGuesses;
	int remainingGuesses {6};
	for (long long unsigned i = 0; i < word.length(); ++i) {
		guessString += "_ ";
	}
	std::cout << "\033[2J\033[1;1H"; //ANSI escape sequence to clear the screen
	std::cout << "-------------------\n";
	std::cout << "Welcome to hangman!\n";
	std::cout << "-------------------\n";
	
	while(remainingGuesses >= 0) {
		printMan(remainingGuesses);
		if (remainingGuesses == 0) {
			std::cout << "Out of guesses!\n";
			std::cout << "The word was: \"" << word << "\"\n";
			break;
		}
		std::cout << guessString << '\n';
		if (!inWord('_', guessString)) {
			std::cout << "You win, Congratulations!\n";
			break;
		}
		char guess {getGuess()};
		if (wasGuessed(guess, previousGuesses)) {
			std::cout << "You already guessed " << guess << "!\n";
			continue;
		} else {
			previousGuesses.push_back(guess);
		}
		if (inWord(guess, word)) {
			std::cout << guess << " is in the word!\n";
			replace(guess, word, guessString);
		} else {
			std::cout << guess << " was not in the word\n";
			--remainingGuesses;
		}
	}
	std::cout << "Press enter to exit...\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for clearing screen
}