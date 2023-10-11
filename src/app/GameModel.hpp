#pragma once

#include <pch.hpp>
#include <GameTile.hpp>

namespace game
{

struct Position
{
    uint64_t row;
    uint64_t column;
};

class GameModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(GameModel)

    Q_PROPERTY(uint64_t boardSize READ boardSize NOTIFY boardSizeChanged)
    Q_PROPERTY(bool gameResult READ gameResult NOTIFY gameResultChanged)

    static constexpr uint64_t DEFAULT_BOARD_SIZE { 4 };

    enum Role
    {
        NumberRole = Qt::ItemDataRole::UserRole,
        IsBlankRole,
        IndexRole

    }; // enum class Role

public:
    explicit GameModel(QObject *parent = nullptr);
    ~GameModel() override = default;

    Q_INVOKABLE void setupBoard(const uint64_t boardSize);
    Q_INVOKABLE void newGame();
    Q_INVOKABLE void resetGame();

    Q_INVOKABLE void moveElement(const uint64_t elementIndex);

    [[nodiscard]] uint64_t boardSize() const noexcept;
    [[nodiscard]] bool gameResult() const noexcept;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;
    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

private:
    void shuffle();

    [[nodiscard]] bool isMoveLegal(const uint64_t currentElementIndex, const uint64_t blankElementIndex) const noexcept;
    [[nodiscard]] uint64_t getBlankElementIndex() const noexcept;
    [[nodiscard]] Position getElementPosition(const uint64_t elementIndex) const noexcept;
    [[nodiscard]] static uint64_t getDistance(const uint64_t firstElementIndex, const uint64_t secondElementIndex) noexcept;

    [[nodiscard]] bool isSolvable();
    [[nodiscard]] uint64_t calculateInversions() const;

    [[nodiscard]] bool checkCurrentState() const;

    void setBoardSize(const uint64_t value);
    void setGameResult(const bool value);

private:
    QHash<int, QByteArray> m_roleNames;

    uint64_t m_boardSize;
    bool m_gameResult;

    std::vector<GameTile> m_initialState;
    std::vector<GameTile> m_currentState;
    std::vector<GameTile> m_expectedState;

    uint64_t m_blankElementIndex;
    uint64_t m_blankElementValue;

    std::mt19937_64 m_generator;

signals:
    void boardSizeChanged();
    void gameResultChanged();

}; // class GameModel

} // namespace game