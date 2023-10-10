#include <GameModel.hpp>

game::GameModel::GameModel(QObject *parent) :
    QAbstractListModel { parent },
    m_boardSize { DEFAULT_BOARD_SIZE },
    m_gameResult { false }
{
    m_roleNames.emplace(static_cast<int>(Role::NumberRole), "number");
    m_roleNames.emplace(static_cast<int>(Role::IsBlankRole), "isBlank");
    m_roleNames.emplace(static_cast<int>(Role::IndexRole), "index");

    std::random_device randomDevice {};
    m_generator.seed(randomDevice());

    setupBoard(m_boardSize);
}

void game::GameModel::setupBoard(const uint64_t boardSize)
{
    setBoardSize(boardSize);

    m_initialState.resize(std::pow(m_boardSize, 2));
    std::iota(m_initialState.begin(), m_initialState.end(), 1);
    m_blankElementValue = m_initialState.back().value();

    m_expectedState = m_initialState;

    newGame();
}

void game::GameModel::newGame()
{
    shuffle();
    resetGame();
}

void game::GameModel::resetGame()
{
    m_currentState = m_initialState;
    m_blankElementIndex = getBlankElementIndex();

    emit dataChanged(createIndex(0, 0), createIndex(m_currentState.size(), 0));

    setGameResult(false);
}

void game::GameModel::moveElement(const uint64_t elementIndex)
{
    if (elementIndex >= m_currentState.size()) return;

    if (!isMoveLegal(elementIndex, m_blankElementIndex)) return;

    std::swap(m_currentState[elementIndex], m_currentState[m_blankElementIndex]);
    m_blankElementIndex = elementIndex;

    emit dataChanged(createIndex(0, 0), createIndex(m_currentState.size(), 0)); // ???????????

    const bool solved { checkCurrentState() };
    if (solved) setGameResult(true);
}

uint64_t game::GameModel::boardSize() const noexcept { return m_boardSize; }
uint64_t game::GameModel::blankElementValue() const noexcept { return m_blankElementValue; }
bool game::GameModel::gameResult() const noexcept { return m_gameResult; }

QHash<int, QByteArray> game::GameModel::roleNames() const { return m_roleNames; }

int game::GameModel::rowCount(const QModelIndex &parent) const
{
    const int result { !parent.isValid() ? static_cast<int>(m_currentState.size()) : 0 };
    return result;
}

QVariant game::GameModel::data(const QModelIndex &index, int role) const
{
    const int rowIndex { index.row() };
    if (!index.isValid() || rowIndex >= m_currentState.size()) return QVariant {};

    const Role castedRole { static_cast<Role>(role) };

    QVariant result {};
    switch (castedRole)
    {
        case Role::NumberRole: result = QVariant::fromValue(m_currentState[rowIndex].value()); break;
        case Role::IsBlankRole: result = QVariant::fromValue(m_currentState[rowIndex].value() == m_blankElementValue); break;
        case Role::IndexRole: result = QVariant::fromValue(rowIndex); break;
        default: break;
    }
    return result;
}

void game::GameModel::shuffle()
{
    do
    {
        std::shuffle(m_initialState.begin(), m_initialState.end(), m_generator);
    }
    while (!isSolvable());
}

uint64_t game::GameModel::getBlankElementIndex() const noexcept
{
    const auto blankElementIt { std::find(m_initialState.begin(), m_initialState.end(),
                                          m_blankElementValue) };
    const int64_t result { blankElementIt - m_initialState.begin() };
    return static_cast<uint64_t>(result);
}

bool game::GameModel::isMoveLegal(const uint64_t currentElementIndex, const uint64_t blankElementIndex) const noexcept
{
    if (currentElementIndex == blankElementIndex) return false;

    const Position currentElementPosition { getElementPosition(currentElementIndex) };
    const Position blankElementPosition { getElementPosition(blankElementIndex) };

    uint64_t distance {};
    if (currentElementPosition.row == blankElementPosition.row)
    {
        distance = getDistance(currentElementPosition.column, blankElementPosition.column);
    }
    else if (currentElementPosition.column == blankElementPosition.column)
    {
        distance = getDistance(currentElementPosition.row, blankElementPosition.row);
    }

    const bool result { distance == 1 };
    return result;
}

game::Position game::GameModel::getElementPosition(const uint64_t elementIndex) const noexcept
{
    const uint64_t row { elementIndex / m_boardSize };
    const uint64_t column { elementIndex % m_boardSize };

    const Position result { row, column };
    return result;
}

uint64_t game::GameModel::getDistance(const uint64_t firstElementIndex, const uint64_t secondElementIndex) noexcept
{
    const int64_t result { std::abs(static_cast<int64_t>(firstElementIndex) - static_cast<int64_t>(secondElementIndex)) };
    return result;
}

bool game::GameModel::isSolvable()
{
    const uint64_t inversions { calculateInversions() };

    if (m_boardSize & 1) return !(inversions & 1);

    m_blankElementIndex = getBlankElementIndex();
    const uint64_t blankElementRow { m_boardSize - m_blankElementIndex / m_boardSize };

    const uint64_t result { (blankElementRow & 1) ? !(inversions & 1) : (inversions & 1) };
    return static_cast<bool>(result);
}

uint64_t game::GameModel::calculateInversions() const
{
    uint64_t result { 0 };

    for (uint64_t i { 0 }; i < m_initialState.size() - 1; ++i)
    {
        for (uint64_t j { i + 1 }; j < m_initialState.size(); ++j)
        {
            if (m_initialState[i].value() == m_initialState.size()) continue;
            if (m_initialState[j].value() == m_initialState.size()) continue;
            if (m_initialState[i] <= m_initialState[j].value()) continue;

            ++result;
        }
    }

    return result;
}

bool game::GameModel::checkCurrentState() const
{
    const bool result { m_currentState == m_expectedState };
    return result;
}

void game::GameModel::setBoardSize(const uint64_t value)
{
    if (m_boardSize == value) return;

    m_boardSize = value;
    emit boardSizeChanged();
}

void game::GameModel::setGameResult(const bool value)
{
    if (m_gameResult == value) return;

    m_gameResult = value;
    emit gameResultChanged();
}