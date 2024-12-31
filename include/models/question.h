        #pragma once
        #include <string>
        #include <vector>

        class Question {
        public:
           Question();
            Question(int id, const std::string& text, const std::string& type);
            int getId() const;
            void setId(int id);

            std::string getText() const;
            void setText(const std::string& text);

            std::string getType() const;
            void setType(const std::string& type);

             static Question create(const std::string& text, const std::string& type);
            static std::vector<Question> getAll();
            static Question get(int id);
             static Question update(int id, const std::string& text, const std::string& type);
            static void remove(int id);
        private:
            int id;
            std::string text;
            std::string type;
            static std::vector<Question> questions;
            static int nextId;
        };
        