          #include "models/answer.h"
          #include <vector>
          #include <stdexcept>

          std::vector<Answer> Answer::answers;
          int Answer::nextId = 1;

          Answer::Answer() : id(0), text(""), isCorrect(false) {}

          Answer::Answer(int id, const std::string& text, bool isCorrect)
              : id(id), text(text), isCorrect(isCorrect) {}

          int Answer::getId() const {
              return id;
          }

          void Answer::setId(int id) {
              this->id = id;
          }

          std::string Answer::getText() const {
              return text;
          }

          void Answer::setText(const std::string& text) {
              this->text = text;
          }

          void Answer::setCorrect(bool correct) {
               isCorrect = correct;
          }
          
          Answer Answer::create(const std::string& text, bool isCorrect)
          {
              Answer answer(nextId++, text, isCorrect);
              answers.push_back(answer);
              return answer;
          }

          std::vector<Answer> Answer::getAll()
          {
              return answers;
          }

          Answer Answer::get(int id)
          {
              for (const auto& answer : answers)
              {
                  if (answer.getId() == id)
                  {
                      return answer;
                  }
              }
              throw std::runtime_error("Answer not found");
          }

          Answer Answer::update(int id, const std::string& text, bool isCorrect)
          {
              for(auto& answer : answers)
            {
              if (answer.getId() == id)
               {
                  answer.setText(text);
                   answer.setCorrect(isCorrect);
                     return answer;
               }
            }
             throw std::runtime_error("Answer not found");
          }

          void Answer::remove(int id)
          {
             for (size_t i = 0; i < answers.size(); ++i)
             {
                if (answers[i].getId() == id)
                {
                   answers.erase(answers.begin() + i);
                     return;
                   }
             }
            throw std::runtime_error("Answer not found");
          }