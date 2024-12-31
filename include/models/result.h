        #pragma once
        #include <vector>

        class Result {
        public:
           Result();
           Result(int id, int userId, int testId, int score);

            int getId() const;
           void setId(int id);

            int getUserId() const;
            void setUserId(int userId);

           int getTestId() const;
            void setTestId(int testId);

          int getScore() const;
          void setScore(int score);

           static Result create(int userId, int testId, int score);
           static std::vector<Result> getAll();
           static Result get(int id);
           static Result update(int id, int userId, int testId, int score);
           static void remove(int id);

        private:
            int id;
            int userId;
            int testId;
           int score;
           static std::vector<Result> results;
           static int nextId;
        };
        