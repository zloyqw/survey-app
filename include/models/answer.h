        #pragma once
        #include <string>
        #include <vector>

        class Answer {
        public:
            Answer();
            Answer(int id, const std::string& text, bool isCorrect);

            int getId() const;
            void setId(int id);

            std::string getText() const;
            void setText(const std::string& text);

            void setCorrect(bool correct);
            
            static Answer create(const std::string& text, bool isCorrect);
            static std::vector<Answer> getAll();
            static Answer get(int id);
            static Answer update(int id, const std::string& text, bool isCorrect);
            static void remove(int id);

        private:
            int id;
            std::string text;
            bool isCorrect;
             static std::vector<Answer> answers;
            static int nextId;
        };
        

   
               
