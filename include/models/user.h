        #pragma once
        #include <string>
        #include <vector>

        class User {
        public:
            User();
            User(int id, const std::string& username, const std::string& email);

            int getId() const;
            void setId(int id);

            std::string getUsername() const;
            void setUsername(const std::string& username);

            std::string getEmail() const;
            void setEmail(const std::string& email);

            static User create(const std::string& username, const std::string& email);
            static std::vector<User> getAll();
            static User get(int id);
            static User update(int id, const std::string& username, const std::string& email);
            static void remove(int id);

        private:
            int id;
            std::string username;
            std::string email;
            static std::vector<User> users;
            static int nextId;
        };
    
