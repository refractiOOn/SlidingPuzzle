#include "GameBoard.hpp"
#include <algorithm>

game::GameBoard::GameBoard(const size_t boardSize, QObject *parent) :
    QAbstractListModel{parent}, m_boardSize{boardSize}
{
    m_initialState.resize(qPow(m_boardSize, 2));

    // Fill the vector with the numbers from 1 to size() - 1
    std::iota(m_initialState.begin(), m_initialState.end(), 1);

    // Set a seed to the random number generator
    std::random_device rd{};
    m_generator.seed(rd());

    // Shuffle the board
    //shuffle();
    newGame();
}

void game::GameBoard::newGame()
{
    shuffle();
    currentToInitial();
}

void game::GameBoard::currentToInitial()
{
    m_currentState = m_initialState;
    emit dataChanged(createIndex(0, 0), createIndex(m_currentState.size(), 0));
}

void game::GameBoard::moveElement(size_t index)
{
    std::function<bool(size_t, size_t)> isLegal = [&](size_t currentElementIndex, size_t hiddenElementIndex)
    {
        std::function<std::pair<size_t, size_t>(const size_t)> getCoordinates = [&](const size_t elementIndex)
        {
            const size_t row = elementIndex / m_boardSize, column = elementIndex % m_boardSize;
            return std::make_pair(row, column);
        };

        std::function<size_t(const size_t, const size_t)> getDistance = [](const size_t first, const size_t second)
        {
            size_t distance = qAbs(static_cast<int>(first) - static_cast<int>(second));
            return distance;
        };

        if (currentElementIndex == hiddenElementIndex) return false;

        const auto currentElementPosition = getCoordinates(currentElementIndex),
            hiddenElementPosition = getCoordinates(hiddenElementIndex);

        if (currentElementPosition.first == hiddenElementPosition.first)
        {
            size_t distance = getDistance(currentElementPosition.second, hiddenElementPosition.second);
            if (distance == 1) return true;
        }
        if (currentElementPosition.second == hiddenElementPosition.second)
        {
            size_t distance = getDistance(currentElementPosition.first, hiddenElementPosition.first);
            if (distance == 1) return true;
        }
        return false;
    };

    if (index >= m_currentState.size()) return;

    size_t hiddenElementIndex = std::find(m_currentState.begin(), m_currentState.end(), m_currentState.size()) - m_currentState.begin();
    if (isLegal(index, hiddenElementIndex))
    {
        std::swap(m_currentState[index], m_currentState[hiddenElementIndex]);
        emit dataChanged(createIndex(0, 0), createIndex(m_currentState.size(), 0));
    }
}

void game::GameBoard::shuffle()
{
    std::shuffle(m_initialState.begin(), m_initialState.end(), m_generator);
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


size_t game::GameBoard::boardSize() const
{
    return m_boardSize;
}

size_t game::GameBoard::tilesNumber() const
{
    return m_currentState.size();
}
