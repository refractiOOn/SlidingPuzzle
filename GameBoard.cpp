#include "GameBoard.hpp"
#include <algorithm>

game::GameBoard::GameBoard(const size_t boardSize, QObject *parent) :
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

void game::GameBoard::newGame()
{
    shuffle();
    currentToInitial();
}

void game::GameBoard::currentToInitial()
{
    // Return the current board state to the starting position
    m_currentState = m_initialState;
    setPuzzleSolved(false);
    emit dataChanged(createIndex(0, 0), createIndex(m_currentState.size(), 0));
}

void game::GameBoard::moveElement(size_t index)
{
    std::function<bool(size_t, size_t)> isLegal = [this](size_t currentIndex, size_t blankIndex)
    {
        std::function<std::pair<size_t, size_t>(const size_t)> getCoordinates = [this](const size_t elementIndex)
        {
            const size_t row = elementIndex / m_boardSize, column = elementIndex % m_boardSize;
            return std::make_pair(row, column);
        };

        std::function<size_t(const size_t, const size_t)> getDistance = [](const size_t first, const size_t second)
        {
            size_t distance = qAbs(static_cast<int>(first) - static_cast<int>(second));
            return distance;
        };

        if (currentIndex == blankIndex) return false;

        const auto currentElementPosition = getCoordinates(currentIndex),
            blankElementPosition = getCoordinates(blankIndex);

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
    };

    if (index >= m_currentState.size()) return;

    size_t blankElementIndex = std::find(m_currentState.begin(), m_currentState.end(), 0) - m_currentState.begin();
    if (isLegal(index, blankElementIndex))
    {
        std::swap(m_currentState[index], m_currentState[blankElementIndex]);
        emit dataChanged(createIndex(0, 0), createIndex(m_currentState.size(), 0));

        if (checkCurrentState())
        {
            setPuzzleSolved(true);
        }
    }
}

size_t game::GameBoard::boardSize() const
{
    return m_boardSize;
}

bool game::GameBoard::puzzleSolved() const
{
    return m_puzzleSolved;
}

void game::GameBoard::shuffle()
{
    std::function<size_t()> calculateInversions = [this]()
    {
        size_t res{};

        for (size_t i = 0; i < m_initialState.size() - 1; ++i)
        {
            for (size_t j = i + 1; j < m_initialState.size(); ++j)
            {
                if (m_initialState[i].value() and m_initialState[j].value()
                    and m_initialState[i].value() > m_initialState[j].value())
                    ++res;
            }
        }

        return res;
    };
    std::function<size_t()> blankElementRow = [this]()
    {
        size_t index = std::find(m_initialState.begin(), m_initialState.end(), 0) - m_initialState.begin();
        size_t defaultRow = index / m_boardSize;
        size_t rowFromEnd = m_boardSize - defaultRow;
        return rowFromEnd;
    };

    std::function<bool()> isSolvable = [this, &calculateInversions, &blankElementRow]()
    {
        size_t inversionCount = calculateInversions();

        if (m_boardSize & 1)
        {
            return !(inversionCount & 1);
        }

        size_t row = blankElementRow();
        bool res = (row & 1) ? !(inversionCount & 1) : inversionCount & 1;
        return res;
    };

    do
    {
        std::shuffle(m_initialState.begin(), m_initialState.end(), m_generator);
    }
    while (!isSolvable());
}

int game::GameBoard::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_currentState.size();
}

QVariant game::GameBoard::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() or role != Qt::DisplayRole)
        return QVariant{};

    const size_t value = m_currentState.at(index.row()).value();
    return QVariant::fromValue(value);
}

void game::GameBoard::setPuzzleSolved(bool value)
{
    if (m_puzzleSolved == value)
        return;

    m_puzzleSolved = value;
    emit puzzleSolvedChanged();
}

bool game::GameBoard::checkCurrentState() const
{
    for (size_t i = 0; i < m_currentState.size(); ++i)
    {
        if (m_currentState[i].value() != m_expectedState[i].value())
            return false;
    }
    return true;
}
