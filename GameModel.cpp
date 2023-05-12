#include "GameModel.hpp"
#include <algorithm>

game::GameModel::GameModel(const size_t boardSize, QObject *parent) :
    QAbstractListModel{parent}, m_boardSize{boardSize}
{
    // Fill the vector with the numbers [0, size)
    m_initialState.resize(qPow(m_boardSize, 2));
    std::iota(m_initialState.begin(), m_initialState.end(), 0);

    m_expectedState.resize(qPow(m_boardSize, 2));
    std::iota(m_expectedState.begin(), m_expectedState.begin() + (m_expectedState.size() - 1), 1);

    // Set a seed to the random number generator
    std::random_device rd{};
    m_generator.seed(rd());

    // Shuffle the board
    newGame();
}

void game::GameModel::newGame()
{
    shuffle();
    currentToInitial();
}

void game::GameModel::currentToInitial()
{
    // Return the current board state to the starting position
    m_currentState = m_initialState;
    setPuzzleSolved(false);
    emit dataChanged(createIndex(0, 0), createIndex(m_currentState.size(), 0));
}

void game::GameModel::moveElement(const size_t currentElement)
{
    if (currentElement >= m_currentState.size()) return;

    size_t blankElement = std::find(m_currentState.begin(), m_currentState.end(), 0) - m_currentState.begin();
    if (isMoveLegal(currentElement, blankElement))
    {
        std::swap(m_currentState[currentElement], m_currentState[blankElement]);
        emit dataChanged(createIndex(0, 0), createIndex(m_currentState.size(), 0));

        if (checkCurrentState())
        {
            setPuzzleSolved(true);
        }
    }
}

size_t game::GameModel::boardSize() const
{
    return m_boardSize;
}

bool game::GameModel::puzzleSolved() const
{
    return m_puzzleSolved;
}

int game::GameModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_currentState.size();
}

QVariant game::GameModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() or role != Qt::DisplayRole)
        return QVariant{};

    const size_t value = m_currentState.at(index.row()).value();
    return QVariant::fromValue(value);
}

void game::GameModel::shuffle()
{
    do
    {
        std::shuffle(m_initialState.begin(), m_initialState.end(), m_generator);
    }
    while (!isBoardSolvable());
}

bool game::GameModel::isMoveLegal(const size_t currentElementIndex, const size_t blankElementIndex) const
{
    if (currentElementIndex == blankElementIndex) return false;

    const position currentElementPosition = getElementPosition(currentElementIndex),
        blankElementPosition = getElementPosition(blankElementIndex);

    if (currentElementPosition.first == blankElementPosition.first)
    {
        size_t distance = getDistance(currentElementPosition.second, blankElementPosition.second);
        if (distance == 1) return true;
    }
    if (currentElementPosition.second == blankElementPosition.second)
    {
        size_t distance = getDistance(currentElementPosition.first, blankElementPosition.first);
        if (distance == 1) return true;
    }
    return false;
}

game::GameModel::position game::GameModel::getElementPosition(const size_t elementIndex) const
{
    const size_t row = elementIndex / m_boardSize, column = elementIndex % m_boardSize;
    return std::make_pair(row, column);
}

size_t game::GameModel::getDistance(const size_t firstElement, const size_t secondElement) const
{
    size_t distance = qAbs(static_cast<int>(firstElement) - static_cast<int>(secondElement));
    return distance;
}

bool game::GameModel::isBoardSolvable()
{
    size_t inversions = calculateInversions();

    if (m_boardSize & 1)
    {
        return !(inversions & 1);
    }

    size_t blankElementIndex = std::find(m_initialState.begin(), m_initialState.end(), 0) - m_initialState.begin();
    size_t blankElementRow = m_boardSize - blankElementIndex / m_boardSize;
    return (blankElementRow & 1) ? !(inversions & 1) : inversions & 1;
}

size_t game::GameModel::calculateInversions() const
{
    size_t inversions{};

    for (size_t i = 0; i < m_initialState.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < m_initialState.size(); ++j)
        {
            if (m_initialState[i].value() and m_initialState[j].value()
                and m_initialState[i].value() > m_initialState[j].value())
                ++inversions;
        }
    }

    return inversions;
}

void game::GameModel::setPuzzleSolved(bool value)
{
    if (m_puzzleSolved == value) return;

    m_puzzleSolved = value;
    emit puzzleSolvedChanged();
}

bool game::GameModel::checkCurrentState() const
{
    for (size_t i = 0; i < m_currentState.size(); ++i)
    {
        if (m_currentState[i].value() != m_expectedState[i].value())
            return false;
    }
    return true;
}
