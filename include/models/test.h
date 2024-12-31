          #pragma once
          #include <string>
          #include <vector>

          class Test {
          public:
              Test();
              Test(int id, const std::string& name, const std::string& description);

              int getId() const;
              void setId(int id);

              std::string getName() const;
              void setName(const std::string& name);

              std::string getDescription() const;
              void setDescription(const std::string& description);
                static Test create(const std::string& name, const std::string& description);
                static std::vector<Test> getAll();
                static Test get(int id);
                static Test update(int id, const std::string& name, const std::string& description);
                static void remove(int id);

          private:
              int id;
              std::string name;
              std::string description;
              static std::vector<Test> tests;
               static int nextId;
          };
          