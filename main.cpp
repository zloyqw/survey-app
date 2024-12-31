#include <iostream>
#include "models/user.h"
#include "models/test.h"
#include "models/question.h"
#include "models/answer.h"
#include "models/result.h"

int main() {
    // --- User Tests ---
    std::cout << "--- User Tests ---" << std::endl;
    User newUser;
    {
        newUser = User::create("test_user_db", "test_db@example.com");
        std::cout << "User created with id: " << newUser.getId() << std::endl;

        User retrievedUser = User::get(newUser.getId());
        std::cout << "User retrieved with id: " << retrievedUser.getId() << ", name: " << retrievedUser.getUsername() << ", email: " << retrievedUser.getEmail() << std::endl;

        std::vector<User> allUsers = User::getAll();
        std::cout << "Number of users: " << allUsers.size() << std::endl;

        User updatedUser = User::update(newUser.getId(), "updated_user_db", "updated_db@example.com");
        std::cout << "User updated with id: " << updatedUser.getId() << ", name: " << updatedUser.getUsername() << ", email: " << updatedUser.getEmail() << std::endl;
    }
    // --- Test Tests ---
    std::cout << "--- Test Tests ---" << std::endl;
    Test newTest;
    {
        newTest = Test::create("test_name", "test_description");
        std::cout << "Test created with id: " << newTest.getId() << std::endl;

        Test retrievedTest = Test::get(newTest.getId());
        std::cout << "Test retrieved with id: " << retrievedTest.getId() << ", name: " << retrievedTest.getName() << ", description: " << retrievedTest.getDescription() << std::endl;

        std::vector<Test> allTests = Test::getAll();
        std::cout << "Number of tests: " << allTests.size() << std::endl;

        Test updatedTest = Test::update(newTest.getId(), "updated_test_name", "updated_test_description");
        std::cout << "Test updated with id: " << updatedTest.getId() << ", name: " << updatedTest.getName() << ", description: " << updatedTest.getDescription() << std::endl;
    }
    // --- Question Tests ---
    std::cout << "--- Question Tests ---" << std::endl;
    Question newQuestion;
    {
         newQuestion = Question::create(newTest.getId(), "question_text");
        std::cout << "Question created with id: " << newQuestion.getId() << ", test id: " << newQuestion.getTestId() << std::endl;

        Question retrievedQuestion = Question::get(newQuestion.getId());
        std::cout << "Question retrieved with id: " << retrievedQuestion.getId() << ", test id: " << retrievedQuestion.getTestId() << ", text: " << retrievedQuestion.getQuestionText() << std::endl;

        std::vector<Question> allQuestions = Question::getAll();
        std::cout << "Number of questions: " << allQuestions.size() << std::endl;

        Question updatedQuestion = Question::update(newQuestion.getId(), newTest.getId(), "updated_question_text");
        std::cout << "Question updated with id: " << updatedQuestion.getId() << ", test id: " << updatedQuestion.getTestId() << ", text: " << updatedQuestion.getQuestionText() << std::endl;
    }
    // --- Answer Tests ---
    std::cout << "--- Answer Tests ---" << std::endl;
    Answer newAnswer;
    {
        newAnswer = Answer::create(newQuestion.getId(), "answer_text", true);
         std::cout << "Answer created with id: " << newAnswer.getId() << ", question id: " << newAnswer.getQuestionId() << ", is correct: " << newAnswer.isCorrectAnswer() <<  std::endl;
        
         Answer retrievedAnswer = Answer::get(newAnswer.getId());
          std::cout << "Answer retrieved with id: " << retrievedAnswer.getId() << ", question id: " << retrievedAnswer.getQuestionId() << ", is correct: " << retrievedAnswer.isCorrectAnswer() << ", text: " << retrievedAnswer.getAnswerText() << std::endl;

         std::vector<Answer> allAnswers = Answer::getAll();
         std::cout << "Number of answers: " << allAnswers.size() << std::endl;

        Answer updatedAnswer = Answer::update(newAnswer.getId(), newQuestion.getId(), "updated_answer_text", false);
         std::cout << "Answer updated with id: " << updatedAnswer.getId() << ", question id: " << updatedAnswer.getQuestionId() << ", is correct: " << updatedAnswer.isCorrectAnswer() <<  ", text: " << updatedAnswer.getAnswerText() << std::endl;
    }
    
     // --- Result Tests ---
    std::cout << "--- Result Tests ---" << std::endl;
     Result newResult;
    {
        newResult = Result::create(newUser.getId(), newTest.getId(), 100);
        std::cout << "Result created with id: " << newResult.getId() << ", user id: " << newResult.getUserId() << ", test id: " << newResult.getTestId() << ", score: " << newResult.getScore() << std::endl;
        
        Result retrievedResult = Result::get(newResult.getId());
        std::cout << "Result retrieved with id: " << retrievedResult.getId() << ", user id: " << retrievedResult.getUserId() << ", test id: " << retrievedResult.getTestId() << ", score: " << retrievedResult.getScore() << std::endl;

        std::vector<Result> allResults = Result::getAll();
        std::cout << "Number of results: " << allResults.size() << std::endl;

        Result updatedResult = Result::update(newResult.getId(), newUser.getId(), newTest.getId(), 150);
         std::cout << "Result updated with id: " << updatedResult.getId() << ", user id: " << updatedResult.getUserId() << ", test id: " << updatedResult.getTestId() << ", score: " << updatedResult.getScore() << std::endl;
    }
   //Delete in right order
    Result::remove(newResult.getId());
    Answer::remove(newAnswer.getId());
    Question::remove(newQuestion.getId());
    Test::remove(newTest.getId());
    User::remove(newUser.getId());
    
    return 0;
}
