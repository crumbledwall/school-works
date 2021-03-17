<template>
  <div>
    <Nav />
    <Sentence />
  </div>
</template>

<script>
import Sentence from '../../components/Sentence'
import Nav from '../../components/Nav'

export default {
  name: 'details',
  components: {
    Sentence,
    Nav
  }
}
</script>

